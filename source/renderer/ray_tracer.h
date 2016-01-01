#ifndef HELIOS_RAY_TRACER_H
#define HELIOS_RAY_TRACER_H

#include "renderer.h"

class RayTracer : public Renderer {
protected:
    ImageSize image_size;

    virtual void shade();

public:
    RayTracer(const ImageSize &image_size) : image_size(image_size)
    { }

    void render();
};

#endif //HELIOS_RAY_TRACER_H
