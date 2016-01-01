#ifndef HELIOS_SPHERE_H
#define HELIOS_SPHERE_H

#include "object.h"

class Sphere : public Object {
protected:
    Vec3 center;
    double radius = 0;

public:
    Sphere() = default;

    Sphere(const Vec3 &center, double radius) : center(center), radius(radius)
    { };

    bool intersect(const Ray &ray, HitPoint *hit_point);
};

#endif //HELIOS_SPHERE_H
