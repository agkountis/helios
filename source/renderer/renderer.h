#ifndef HELIOS_RENDERER_H
#define HELIOS_RENDERER_H

struct ImageSize {
    unsigned int width = 0;
    unsigned int height = 0;
};

class Renderer {
protected:
    virtual void shade() = 0;

    virtual void trace_ray(const Ray &ray) = 0;

public:
    virtual ~Renderer() = default;

    virtual void render() = 0;
};

#endif //HELIOS_RENDERER_H
