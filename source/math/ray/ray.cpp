#include "ray.h"

Ray::Ray(const Vec3 &origin, const Vec3 &direction)
{
    this->origin = origin;
    this->direction = direction;
}
