/*
Helios-Ray - A powerful and highly configurable renderer
Copyright (C) 2016  Angelos Gkountis

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <iostream>

#ifdef _WIN32
#define _USE_MATH_DEFINES
#endif

#include <math.h>
#include <material.h>
#include <drawable.h>
#include <limits>
#include <chrono>
#include <assert.h>
#include "ray_tracer.h"

using namespace std::chrono;

RayTracer::~RayTracer()
{
    delete scene;
}

bool RayTracer::initialize()
{
    float *pixels = image.get_pixels();

    unsigned int image_width = image.get_width();

    std::cout << "Creating render jobs..." << std::endl;

    for (unsigned int x = 0; x < image.get_height(); x++) {
        this->render_jobs.push_back([this, x, image_width, pixels] {
            render_scan_line(x, image_width, pixels);
        });
    }

    std::cout << "Done creating jobs!" << std::endl;

    return true;
}

void RayTracer::set_image(const Image &image)
{
    this->image = image;
}

void RayTracer::set_scene(const Scene *scene)
{
    this->scene = scene;
}

void RayTracer::render()
{
    if (!scene) {
        std::cerr << "RayTracer ERROR: Scene pointer is null." << std::endl;
        exit(1);
    }

    thread_pool.initialize();

    high_resolution_clock::time_point start = high_resolution_clock::now();

    std::cout << "Adding render jobs..." << std::endl;

    thread_pool.add_jobs(render_jobs);

    std::cout << "Jobs added, rendering starts..." << std::endl;

    thread_pool.wait();

    high_resolution_clock::time_point end = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(end - start).count() / 1000.0;

    std::cout << "Rendering completed in " << duration << "ms" << std::endl;

}

Vec3 RayTracer::shade(const Ray &ray, HitPoint &hit_point, int iterations)
{
    Vec3 color;

    Material material = ((Drawable *) hit_point.object)->material;

    Vec3 view_direction = -ray.direction;
    view_direction.normalize();

    const std::vector<Light *> &lights = scene->get_lights();

    for (auto light : lights) {

        /**
         * Create a shadow ray from the object hit point towards the current light in the loop.
         */
        Ray shadow_ray(hit_point.position, light->get_position() - hit_point.position);

        HitPoint shadow_hit_point;
        shadow_hit_point.distance = std::numeric_limits<float>::max();

        /**
         * Check for intersections with other objects.
         * If an intersection is found then the being shaded is obscured by another object thus it is in shadow.
         */
        find_intersection(shadow_ray, shadow_hit_point);

        /**
         * If an object is hit skip lighting calculations.
         */
        if (shadow_hit_point.object && shadow_hit_point.distance < 1.0)
            continue;

        Vec3 light_direction = light->get_position() - hit_point.position;
        light_direction.normalize();

        float diff_light = shader.calculate_diffuse_contribution(light_direction, view_direction, hit_point, material);

        float f_reflective = shader.calculate_specular_contribution(hit_point.normal, light_direction, view_direction, material);

        Vec3 col = ((material.albedo * diff_light) / M_PI) * material.roughness;
        col = material.metallic ? col + material.albedo * f_reflective : col + Vec3(1.0, 1.0, 1.0) * f_reflective;

        color = color + col * light->get_color();
    }

    float reflectivity = (1.0f - material.roughness);

    if (reflectivity > 0.0001) {

        Vec3 refl_dir = reflect(ray.direction, hit_point.normal);
        float brdf = shader.calculate_specular_contribution(hit_point.normal, refl_dir.normalized(), view_direction, material);

        //TODO: Move this in the brdf eval and use radiometric or photometric lights.
        reflectivity *= brdf > 1.0f ? 1.0f : brdf;

        if (reflectivity > 0.0001) {
            Ray reflection_ray = Ray(hit_point.position, refl_dir);
            reflection_ray.energy = ray.energy * reflectivity;
            Vec3 refl_color = material.metallic ? material.albedo * reflectivity : Vec3(1.0, 1.0, 1.0) * reflectivity;
            color = color + trace_ray(reflection_ray, iterations + 1) * refl_color;
        }
    }

    return color;
}

Vec3 RayTracer::trace_ray(const Ray &ray, int iterations)
{
    if (iterations > max_iterations || ray.energy < energy_threshold) {
        return Vec3(0.0, 0.0, 0.0);
    }

    HitPoint nearest;
    nearest.distance = std::numeric_limits<float>::max();

    find_intersection(ray, nearest);

    if (!nearest.object) {
        return Vec3(0.0, 0.0, 0.0);
    }

    Vec3 color = shade(ray, nearest, iterations);

    return color;
}

void RayTracer::find_intersection(const Ray &ray, HitPoint &hit_point)
{
    for (unsigned int i = 0; i < scene->get_drawable_count(); i++) {
        Drawable *obj = scene->get_drawable(i);

        HitPoint pt;

        if (obj->intersect(ray, &pt) && pt.distance < hit_point.distance) {
            hit_point = pt;
        }
    }
}

Ray RayTracer::create_primary_ray(int pixel_x, int pixel_y) const
{
    int image_width = image.get_width();
    int image_height = image.get_height();

    float aspect = (float) image_width / (float) image_height;

    auto camera = scene->get_camera();
    float camera_fov = camera.get_fov();

    Ray ray;

    /**
     * The ray origin is at 0 0 0 so we don't touch it.
     */
    //ray.origin = camera.get_position();

    ray.direction.x = (2.0f * (float) pixel_x / (float) image_width - 1.0f) * aspect;
    ray.direction.y = 1.0f - 2.0f * (float) pixel_y / (float) image_height;
    ray.direction.z = 1.0f / (float) tan(camera_fov / 2.0f);

    ray.direction.normalize();

    camera.calculate_transformation();
    ray.transform(camera.get_transformation_matrix());

    return ray;
}


void RayTracer::render_scan_line(unsigned int line_number, unsigned int line_size, float *pixels)
{
    /**
     * Advance the pointer to the correct line starting point.
     */
    pixels += (line_number * line_size * 3);

    for (unsigned int y = 0; y < line_size; y++) {

        Ray primary_ray = create_primary_ray(y, line_number);

        Vec3 color = trace_ray(primary_ray);

        image.tone_map_pixel(&color.x, &color.y, &color.z);

        /**
        * Gamma correction
        */
        color.x = (float) pow(color.x, 0.45454545f);
        color.y = (float) pow(color.y, 0.45454545f);
        color.z = (float) pow(color.z, 0.45454545f);

        *pixels++ = color.x;
        *pixels++ = color.y;
        *pixels++ = color.z;
    }
}
