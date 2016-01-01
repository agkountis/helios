#include "sphere.h"
#include <math.h>

bool Sphere::intersect(const Ray &ray, HitPoint *hit_point)
{
    /**
     * sphere vector equation is |x - center| = radius
     * can also be written as (x - center) * (x - center) = radius^2
     * the ray equation is x = pos - dir * t;
     * replacing x into the sphere equation we get
     * (origin - direction * t - center) * (origin - direction * t - center) = radius^2
     *
     *  parameter of the resulting quadratic equation
     *
     *  A = dir^2
     *  B = 2 * direction * (origin - center)
     *  C = (origin - center)^2 - radius^2
     */

    Vec3 dist_vec = ray.origin - center;

    double dist_squared = dot(dist_vec, dist_vec);

    /**
     * The ray origin is within the sphere so we don't consider it an intersection.
     */
    if(dist_squared < radius * radius)
        return false;


    double a = dot(ray.direction, ray.direction);

    double b = 2.0 * dot(ray.direction, ray.origin - center);

    double c = dist_squared - radius * radius;


    double disc = b * b - (4.0 * a * c);

    /**
     * If the discriminant is < 0 we have no intersection.
     */
    if(disc < 1e-4)
        return false;

    double disc_sqrt = sqrt(disc);

    double t0 = -b + disc_sqrt / 2.0 * a;

    double t1 = -b - disc_sqrt / 2.0 * a;



    return false;
}
