#include "plane.h"


void Plane::set_normal(const Vec3 &normal)
{
    this->normal = normal;
}

const Vec3 &Plane::get_normal() const
{
    return normal;
}

bool Plane::intersect(const Ray &ray, HitPoint *hit_point)
{
    //ray -> x = orig - dir * t
    //plane -> x = (dot(ray.orig, normal) + d) / dot(ray.dir, normal)
    //d = -normal.x * pos.x - normal.y * pos.y - normal.z * pos.z

    /**
     * Distance of the plane from the world origin.
     */
    float d = position.length();

    float n_dot_rdir = dot(normal, ray.direction);

    /**
     * Ray parallel to the plane. No intersection
     */
    if(n_dot_rdir == 0)
        return false;

    /**
     * Plane faces away from the ray. The plane is culled.
     */
    if(n_dot_rdir > 0.0001)
        return false;


    float t = -(dot(normal, ray.origin) + d) / n_dot_rdir;

    /**
     * Intersection point is behind the ray. No real intersections.
     */
    if (t < 0)
        return false;

    hit_point->position = ray.origin + ray.direction * t;
    hit_point->normal = normal;
    hit_point->distance = t;
    hit_point->object = this;

    return true;
}
