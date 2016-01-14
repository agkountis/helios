#include <math.h>
#include "vec3.h"

float Vec3::length()
{
    return (float)sqrt(x * x + y * y + z * z);
}

float Vec3::length_squared()
{
    return x * x + y * y + z * z;
}

void Vec3::normalize()
{
    float length = this->length();

    if(length) {
        x /= length;
        y /= length;
        z /= length;
    }
}

Vec3 Vec3::normalized()
{
    float length = this->length();

    if(!length)
        return Vec3();

    return Vec3(x / length, y / length, z / length);
}