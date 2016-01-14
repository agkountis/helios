#include <iostream>
#include <math.h>
#include <limits>
#include <material.h>
#include <drawable.h>
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
    for (int x = 0; x < image.get_height(); x++) {
        for (int y = 0; y < image.get_width(); y++) {

            Ray primary_ray = create_primary_ray(y, x);

            Vec3 color;

            HitPoint nearest;
            nearest.distance = std::numeric_limits<float>::max();

            find_intersection(primary_ray, &nearest);

            if (nearest.object) {

                shade(&nearest);

                color = shade(&nearest);
                image.tone_map_pixel(&color.x, &color.y, &color.z);
            }

            *pixels++ = color.x;
            *pixels++ = color.y;
            *pixels++ = color.z;
        }
    }
}

Vec3 RayTracer::shade(HitPoint *hit_point)
{
    Material material = ((Drawable*)hit_point->object)->material;

    Light *lt = scene->get_light(0);

    Vec3 ldir = lt->get_position() - scene->get_camera().get_position();
    Vec3 vdir = -scene->get_camera().get_position();

    ldir.normalize();
    vdir.normalize();

    Vec3 reflection = reflect(-ldir, hit_point->normal);

    float diff_light = std::max(dot(hit_point->normal, ldir), 0.0f);
    float spec_light = (float)pow(std::max(dot(reflection, vdir), 0.0f), 60.0f);

    Vec3 diff_color = material.color * lt->get_color() * diff_light;
    Vec3 spec_color = Vec3(1.0f, 1.0f, 1.0f) * spec_light;

    return diff_color + spec_color;
}

Vec3 RayTracer::trace_ray(const Ray &ray)
{
    return Vec3();
}


void RayTracer::find_intersection(const Ray &ray, HitPoint *hit_point)
{
    for (unsigned int i = 0; i < scene->get_drawable_count(); i++) {
        Collidable *obj = scene->get_drawable(i);

        HitPoint pt;

        if (obj->intersect(ray, &pt) && pt.distance < hit_point->distance) {
            *hit_point = pt;
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
    ray.direction.x = (2.0f * (float) pixel_x / (float) image_width - 1.0f) * aspect;
    ray.direction.y = 1.0f - 2.0f * (float) pixel_y / (float) image_height;
    ray.direction.z = 1.0f / (float)tan(camera_fov / 2.0f);

    ray.direction.normalize();

    ray.transform(camera.get_transformation_matrix());

    return ray;
}
