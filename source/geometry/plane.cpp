/*
Helios-Ray - A powerful and highly configurable renderer
Copyright (C) 2016  Angelos Gkountis

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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
