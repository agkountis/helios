#include "box.h"


Box::Box(const Vec3 &position, double length, double width, double height)
        : Collidable(position), length(length), width(width), height(height)
{ }

bool Box::intersect(const Ray &ray, HitPoint *hit_point)
{
    return false;
}
