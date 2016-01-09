#ifndef HELIOS_BOX_H
#define HELIOS_BOX_H

#include "collidable.h"

class Box : public Collidable {
protected:
    double length;
    double width;
    double height;

public:
    Box() = default;

    Box(const Vec3 &position, double length, double width, double height);

    bool intersect(const Ray &ray, HitPoint *hit_point);
};

#endif //HELIOS_BOX_H
