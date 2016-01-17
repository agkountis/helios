#include <math.h>
#include <mat4.h>
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

void Vec3::transform(const Mat4 &matrix)
{
    x = matrix[0][0] * x + matrix[1][0] * y + matrix[2][0] * z + matrix[3][0];
    y = matrix[0][1] * x + matrix[1][1] * y + matrix[2][1] * z + matrix[3][1];
    z = matrix[0][2] * x + matrix[1][2] * y + matrix[2][2] * z + matrix[3][2];
}
