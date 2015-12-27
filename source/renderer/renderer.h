#ifndef HELIOS_RENDERER_H
#define HELIOS_RENDERER_H

#include <iostream>

class Renderer {
public:
    virtual ~Renderer() = default;
    virtual void render() = 0;
};

#endif //HELIOS_RENDERER_H
