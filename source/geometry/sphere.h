#ifndef HELIOS_SPHERE_H
#define HELIOS_SPHERE_H

#include <memory>
#include "object.h"

using namespace std;

class Sphere : public Object {
protected:
    Vec3 center;
    double radius = 0;

public:
    Sphere() = default;

    Sphere(const Vec3 &center, double radius) : center(center), radius(radius)
    { };

    bool intersect(const Ray &ray, unique_ptr<HitPoint> hit_point);
};

#endif //HELIOS_SPHERE_H
