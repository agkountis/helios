#ifndef HELIOS_RAY_H
#define HELIOS_RAY_H

#include <vec3.h>
#include <mat4.h>

class Ray {
public:
    Vec3 origin;
    Vec3 direction;

    Ray() = default;

    Ray(const Vec3 &origin, const Vec3 &direction) : origin(origin), direction(direction)
    { };

    void transform(const Mat4 &matrix);
};

#endif //HELIOS_RAY_H
