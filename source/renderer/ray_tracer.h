#ifndef HELIOS_RAY_TRACER_H
#define HELIOS_RAY_TRACER_H

#include <scene.h>
#include <image.h>
#include "renderer.h"

class RayTracer : public Renderer {
protected:
    const Scene *scene = nullptr;

    Image image;

    void shade();

    Vec3 trace_ray(const Ray &ray);

    void find_intersection(const Ray &ray, HitPoint *hit_point);

public:
    RayTracer() = default;

    RayTracer(const Scene *scene, const Image &image) : scene(scene), image(image)
    { }

    ~RayTracer();

    void set_scene(const Scene *scene);

    void set_image(const Image &image);

    void render();
};

#endif //HELIOS_RAY_TRACER_H
