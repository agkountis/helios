#ifndef HELIOS_SPHERE_H
#define HELIOS_SPHERE_H

#include "drawable.h"

class Sphere : public Drawable {
protected:
    double radius = 0;

public:
    Sphere() = default;

    Sphere(const Vec3 &position, double radius) : Drawable(position), radius(radius)
    { };

    void intersect(const Ray &ray, HitPoint *hit_point);
};

#endif //HELIOS_SPHERE_H
