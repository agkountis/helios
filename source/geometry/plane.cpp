#include "plane.h"


void Plane::set_normal(const Vec3 &normal)
{
    this->normal = normal;
}

const Vec3 &Plane::get_normal() const
{
    return normal;
}

void Plane::intersect(const Ray &ray, HitPoint *hit_point)
{
    //ray -> x = orig - dir * t
    //plane -> x = (dot(ray.orig, normal) + d) / dot(ray.dir, normal)
    //d = -normal.x * pos.x - normal.y * pos.y - normal.z * pos.z
}
