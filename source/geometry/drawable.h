#ifndef HELIOS_DRAWABLE_H
#define HELIOS_DRAWABLE_H

#include <material.h>
#include "object.h"

class Drawable : public Object {
public:
    Material material;

    Drawable(const Vec3 &position) : Object(position)
    { }

    virtual bool intersect(const Ray &ray, HitPoint *hit_point) = 0;
};

#endif //HELIOS_DRAWABLE_H
