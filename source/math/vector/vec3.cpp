#include <math.h>
#include "vec3.h"

Vec3::Vec3(double x, double y, double z) : x(x), y(y), z(z) { }

double Vec3::dot(const Vec3 &vec)
{
    return x * vec.x + y * vec.y + z * vec.z;
}

Vec3 Vec3::cross(const Vec3 &vec)
{
    return Vec3(y * vec.z - z * vec.y, z * vec.x - x * vec.z, x * vec.y - y * vec.z);
}

double Vec3::length()
{
    return sqrt(x * x + y * y + z * z);
}

double Vec3::length_squared()
{
    return x * x + y * y + z * z;
}

void Vec3::normalize()
{
    double length = this->length();

    x /= length;
    y /= length;
    z /= length;
}

Vec3 Vec3::normalized()
{
    double length = this->length();

    return Vec3(x / length, y / length, z / length);
}