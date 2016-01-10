#include <iostream>
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

    /**
     * Work with scan-lines for now.
     */
    for (int height = 0; height < image.get_height(); height++) {
        for (int width = 0; width < image.get_width(); width++) {
            //TODO: Create a primary ray. Trace it and get the final color.

        }
    }
}

void RayTracer::shade()
{

}

Vec3 RayTracer::trace_ray(const Ray &ray)
{
    return Vec3();
}


void RayTracer::find_intersection(const Ray &ray, HitPoint *hit_point)
{

}


Ray RayTracer::create_primary_ray(int pixel_x, int pixel_y) const
{
    int image_width = image.get_width();
    int image_height = image.get_height();

    float aspect = (float)image_width / (float)image_height;

    Ray ray;

    /**
     * The ray origin is at 0 0 0  so we don't touch it.
     */

    ray.direction.x = (((float)pixel_x / (float)image_width) * 2.0 - 1.0) * aspect;

    return Ray();
}
