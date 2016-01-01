#ifndef HELIOS_OBJECT_H
#define HELIOS_OBJECT_H

#include <ray.h>

class Object {
public:
    virtual ~Object() = default;

    virtual bool intersect(const Ray &ray, HitPoint *hit_point) = 0;
};

#endif //HELIOS_OBJECT_H
