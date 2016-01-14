#include "sphere.h"
#include <math.h>

bool Sphere::intersect(const Ray &ray, HitPoint *hit_point)
{
    /**
     * sphere vector equation is |x - position| = radius
     * can also be written as (x - position) * (x - position) = radius^2
     * the ray equation is x = pos - dir * t;
     * replacing x into the sphere equation we get
     * (origin - direction * t - position) * (origin - direction * t - position) = radius^2
     *
     *  parameter of the resulting quadratic equation
     *
     *  A = dir^2
     *  B = 2 * direction * (origin - position)
     *  C = (origin - position)^2 - radius^2
     */

    double a = dot(ray.direction, ray.direction);

    double b = 2 * ray.direction.x * (ray.origin.x - position.x) +
                2 * ray.direction.y * (ray.origin.y - position.x) +
                2 * ray.direction.z * (ray.origin.z - position.z);

    double c = dot(ray.origin, ray.origin) + dot(position, position) - 2 * dot(ray.origin, position) - radius * radius;


    double disc = b * b - (4.0 * a * c);

    /**
     * If the discriminant is < 0 we have no intersection.
     */
    if (disc < 1e-4)
        return false;

    double disc_sqrt = sqrt(disc);

    double t0 = -b + disc_sqrt / 2.0 * a;

    double t1 = -b - disc_sqrt / 2.0 * a;


    /**
     * Choose the minimum positive solution.
     */
    if (t0 < 1e-4)
        t0 = t1;

    if (t1 < 1e-4)
        t1 = t0;

    double t = t0 < t1 ? t0 : t1;

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

    //TODO: Check if the subtraction order is correct here.
    hit_point->normal = ((hit_point->position - position) / radius).normalized();

    return true;
}
