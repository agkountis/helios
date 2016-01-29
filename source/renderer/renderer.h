#ifndef HELIOS_RENDERER_H
#define HELIOS_RENDERER_H


class Renderer {
protected:
    virtual Vec3 shade(const Ray &ray, HitPoint &hit_point, int iterations) = 0;

    virtual Vec3 trace_ray(const Ray &ray, int iterations) = 0;

    virtual void find_intersection(const Ray &ray, HitPoint &hit_point) = 0;

public:
    virtual ~Renderer() = default;

    virtual void render() = 0;
};

#endif //HELIOS_RENDERER_H
