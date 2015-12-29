#ifndef HELIOS_OBJECT_H
#define HELIOS_OBJECT_H

#include <ray.h>

class Object {
public:
    virtual ~Primitive() = default;
    virtual bool intersect(const Ray &ray) = 0;
};

#endif //HELIOS_OBJECT_H
