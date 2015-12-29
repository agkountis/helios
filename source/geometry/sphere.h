#ifndef HELIOS_SPHERE_H
#define HELIOS_SPHERE_H

#include "object.h"

class Sphere : public Object {
protected:
    Vec3 position;
    double radius = 0;

public:
    Sphere() = default;

    Sphere(const Vec3 &position, double radius) : position(position), radius(radius)
    { };

    bool intersect(const Ray &ray);
};

#endif //HELIOS_SPHERE_H
