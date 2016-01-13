#ifndef HELIOS_DRAWABLE_H
#define HELIOS_DRAWABLE_H

#include <material.h>
#include "collidable.h"

class Drawable : public Collidable {
public:
    Material material;

    Drawable(const Vec3 &position) : Collidable(position)
    { }
};

#endif //HELIOS_DRAWABLE_H
