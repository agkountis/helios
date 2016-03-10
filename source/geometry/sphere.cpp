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

#include "sphere.h"
#include <math.h>

bool Sphere::intersect(const Ray &ray, HitPoint *hit_point)
{
    /**
     * sphere vector equation is |x - position| = radius
     * can also be written as (x - position) * (x - position) = radius^2
     * the ray equation is x = origin - direction * t;
     * replacing x into the sphere equation we get
     * (origin - direction * t - position) * (origin - direction * t - position) = radius^2
     *
     *  parameter of the resulting quadratic equation
     *
     *  A = dir^2
     *  B = 2 * direction * (origin - position)
     *  C = (origin - position)^2 - radius^2
     */

    float a = dot(ray.direction, ray.direction);

    float b = 2.0f * ray.direction.x * (ray.origin.x - position.x) +
                2.0f * ray.direction.y * (ray.origin.y - position.y) +
                2.0f * ray.direction.z * (ray.origin.z - position.z);

    float c = dot(ray.origin, ray.origin) + dot(position, position) - 2.0f * dot(ray.origin, position) - radius * radius;


    float disc = b * b - (4.0f * a * c);

    /**
     * If the discriminant is < 0 we have no intersection.
     */
    if (disc < 1e-4)
        return false;

    float disc_sqrt = (float) sqrt(disc);

    float t0 = (-b + disc_sqrt) / (2.0f * a);

    float t1 = (-b - disc_sqrt) / (2.0f * a);


    /**
     * Choose the minimum positive solution.
     */
    if (t0 < 1e-4)
        t0 = t1;

    if (t1 < 1e-4)
        t1 = t0;

    float t = t0 < t1 ? t0 : t1;

    /**
     * If both solutions turn out to be negative we have no intersection.
     */
    if (t < 1e-4)
        return false;

    /**
     * We have a hit!
     * Fill the hit point structure
     */
    hit_point->object = this;
    hit_point->position = ray.origin + ray.direction * t;
    hit_point->distance = t;

    hit_point->normal = (hit_point->position - position) / radius;

    return true;
}
