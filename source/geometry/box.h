#ifndef HELIOS_BOX_H
#define HELIOS_BOX_H

#include "object.h"

class Box : public Object {
protected:
    Vec3 position;
    double length;
    double width;
    double height;

public:
    Box() = default;

    Box(const Vec3 &position, double length, double width, double height);

    bool intersect(const Ray &ray);
};

#endif //HELIOS_BOX_H
