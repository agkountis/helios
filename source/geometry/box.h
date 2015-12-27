#ifndef HELIOS_BOX_H
#define HELIOS_BOX_H

#include "primitive.h"

class Box : public Primitive {
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
