#ifndef HELIOS_SPHERE_H
#define HELIOS_SPHERE_H

#include "collidable.h"


class Sphere : public Collidable {
protected:
    double radius = 0;

public:
    Sphere() = default;

    Sphere(const Vec3 &position, double radius) : Collidable(position), radius(radius)
    { };

    bool intersect(const Ray &ray, HitPoint *hit_point);
};

#endif //HELIOS_SPHERE_H
