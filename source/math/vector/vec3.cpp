#include <math.h>
#include "vec3.h"

Vec3::Vec3(double x, double y, double z) : x(x), y(y), z(z)
{ }

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