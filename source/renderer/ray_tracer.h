#ifndef HELIOS_RAY_TRACER_H
#define HELIOS_RAY_TRACER_H

#include <scene.h>
#include <image.h>
#include <functional>
#include <thread_pool.h>
#include "renderer.h"

class RayTracer : public Renderer {
protected:
    const Scene *scene = nullptr;

    Image image;

    std::vector< std::function<void()> > render_jobs;

    ThreadPool thread_pool;

    static const int max_iterations = 100;

    //Using 1 / 255 as a threshold.
    static constexpr double energy_threshold = 0.003921569;

    Vec3 shade(const Ray &ray, HitPoint &hit_point, int iterations);

    Vec3 trace_ray(const Ray &ray, int iterations = 0);

    void find_intersection(const Ray &ray, HitPoint &hit_point);

    Ray create_primary_ray(int pixel_x, int pixel_y) const;

    void render_scan_line(unsigned int line_number, unsigned int line_size, float *pixels);

public:
    RayTracer() = default;

    RayTracer(const Scene *scene, const Image &image) : scene(scene), image(image)
    { }

    ~RayTracer();

    bool initialize();

    void set_scene(const Scene *scene);

    void set_image(const Image &image);

    void render();
};

#endif //HELIOS_RAY_TRACER_H
