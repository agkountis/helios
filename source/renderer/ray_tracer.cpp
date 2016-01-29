#include <iostream>
#include <math.h>
#include <material.h>
#include <drawable.h>
#include <limits>
#include "ray_tracer.h"

RayTracer::~RayTracer()
{
    delete scene;
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

    float *pixels = image.get_pixels();

    /**
     * Work with scan-lines for now.
     */
    for (int x = 0; x < (int) image.get_height(); x++) {
        for (int y = 0; y < (int) image.get_width(); y++) {

//            if(x == (image.get_height() / 2) && y == (image.get_width() / 2)) {
//                asm volatile("int $3\n");
//            }

            Ray primary_ray = create_primary_ray(y, x);

            Vec3 color = trace_ray(primary_ray);

            *pixels++ = color.x;
            *pixels++ = color.y;
            *pixels++ = color.z;
        }
    }
}

Vec3 RayTracer::shade(const Ray &ray, HitPoint &hit_point, int iterations)
{
    Vec3 color;

    Material material = ((Drawable *) hit_point.object)->material;

    Vec3 view_direction = -ray.direction;

    std::vector<Light *> lights = scene->get_lights();

    for (Light *light : lights) {

        /**
         * Create a shadow ray from the object hit point towards the current light in the loop.
         */
        Ray shadow_ray(hit_point.position, (light->get_position() - hit_point.position).normalized());

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

        Vec3 reflection_vector = -reflect(view_direction, hit_point.normal);

        float diff_light = std::max(dot(light_direction, hit_point.normal), 0.0f);
        float spec_light = (float) pow(std::max(dot(reflection_vector, light_direction), 0.0f), material.shininess);

        color = color + material.diffuse_color * diff_light;
        color = color + material.specular_color * spec_light;

        color = color * light->get_color();
    }

    if (material.reflectivity > 0.0001) {
        Ray reflection_ray = Ray(hit_point.position, reflect(ray.direction, hit_point.normal));
        color = color + trace_ray(reflection_ray, iterations + 1) * material.reflectivity;
    }

    return color;
}

Vec3 RayTracer::trace_ray(const Ray &ray, int iterations)
{
    HitPoint nearest;
    nearest.distance = std::numeric_limits<float>::max();

    find_intersection(ray, nearest);

    if (!nearest.object || iterations > max_iterations) {
        return Vec3(0.0, 0.0, 0.0);
    }

    Vec3 color = shade(ray, nearest, iterations);
    image.tone_map_pixel(&color.x, &color.y, &color.z);

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

    Camera camera = scene->get_camera();
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

    ray.transform(camera.get_transformation_matrix());

    return ray;
}
