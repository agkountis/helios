#include "box.h"


Box::Box(const Vec3 &position, double length, double width, double height)
        : position(position), length(length), width(width), height(height)
{ }

bool Box::intersect(const Ray &ray)
{
    return false;
}
