#ifndef HELIOS_PLANE_H
#define HELIOS_PLANE_H

#include "drawable.h"


class Plane : public Drawable {
private:
    Vec3 normal;

public:
    Plane() = default;

    Plane(const Vec3 &position, const Vec3 &normal) : Drawable(position), normal(normal)
    { }

    void set_normal(const Vec3 &normal);

    const Vec3 &get_normal() const;

    void intersect(const Ray &ray, HitPoint *hit_point);
};

#endif //HELIOS_PLANE_H
