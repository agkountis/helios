#ifndef HELIOS_COLLIDABLE_H
#define HELIOS_COLLIDABLE_H

#include "object.h"

class Collidable : public Object {
public:
    Collidable(const Vec3 &position) : Object(position)
    { }
    virtual bool intersect(const Ray &ray, HitPoint *hit_point) = 0;
};

#endif //HELIOS_COLLIDABLE_H
