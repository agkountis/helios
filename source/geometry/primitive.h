#ifndef HELIOS_PRIMITIVE_H
#define HELIOS_PRIMITIVE_H

#include <ray.h>

class Primitive {
public:
    virtual ~Primitive() = default;
    virtual bool intersect(const Ray &ray) = 0;
};

#endif //HELIOS_PRIMITIVE_H
