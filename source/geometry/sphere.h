#ifndef HELIOS_SPHERE_H
#define HELIOS_SPHERE_H

#include "object.h"


class Sphere : public Object {
protected:
    double radius = 0;

public:
    Sphere() = default;

    Sphere(const Vec3 &position, double radius) : Object(position), radius(radius)
    { };

    bool intersect(const Ray &ray, HitPoint *hit_point);
};

#endif //HELIOS_SPHERE_H
