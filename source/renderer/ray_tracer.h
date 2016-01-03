#ifndef HELIOS_RAY_TRACER_H
#define HELIOS_RAY_TRACER_H

#include <scene.h>
#include "renderer.h"

class RayTracer : public Renderer {
protected:
    ImageSize image_size;

    const Scene *scene = nullptr;

    void shade();

    void trace_ray(const Ray &ray);

public:
    RayTracer(const Scene *scene, const ImageSize &image_size) : scene(scene), image_size(image_size)
    { }

    ~RayTracer();

    void set_scene(const Scene *scene);

    void set_image_size(const ImageSize &image_size);

    void render();
};

#endif //HELIOS_RAY_TRACER_H
