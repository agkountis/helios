#ifndef HELIOS_RAY_H
#define HELIOS_RAY_H

#include <vec3.h>
#include <mat4.h>

class Object;

struct HitPoint {
    Object *object = nullptr;
    Vec3 position;
    Vec3 normal;
    double distance = 0.0;

};

class Ray {
public:
    Vec3 origin;
    Vec3 direction;
    double energy = 1.0;

    Ray() = default;

    Ray(const Vec3 &origin, const Vec3 &direction) : origin(origin), direction(direction)
    { };

    void transform(const Mat4 &matrix);
};

#endif //HELIOS_RAY_H
