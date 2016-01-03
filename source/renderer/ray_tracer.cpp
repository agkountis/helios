#include <iostream>
#include "ray_tracer.h"

RayTracer::~RayTracer()
{
    delete scene;
}

void RayTracer::set_image_size(const ImageSize &image_size)
{
    this->image_size = image_size;
}

void RayTracer::set_scene(const Scene *scene)
{
    this->scene = scene;
}

void RayTracer::render()
{
    if(!scene) {
        std::cerr << "RayTracer ERROR: Scene pointer is null." << std::endl;
        exit(1);
    }



}

void RayTracer::shade()
{

}

void RayTracer::trace_ray(const Ray &ray)
{

}
