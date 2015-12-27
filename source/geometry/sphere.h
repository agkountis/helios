#ifndef HELIOS_SPHERE_H
#define HELIOS_SPHERE_H

#include "primitive.h"

class Sphere : public Primitive {
protected:
    Vec3 position;
    double radius = 0;

public:
    Sphere() = default;

    Sphere(const Vec3 &position, double radius);

    bool intersect(const Ray &ray);
};

#endif //HELIOS_SPHERE_H
