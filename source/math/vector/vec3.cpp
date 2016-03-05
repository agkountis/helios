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
    float new_x = matrix[0][0] * x + matrix[0][1] * y + matrix[0][2] * z + matrix[0][3];
    float new_y = matrix[1][0] * x + matrix[1][1] * y + matrix[1][2] * z + matrix[1][3];
    z = matrix[2][0] * x + matrix[2][1] * y + matrix[2][2] * z + matrix[2][3];
    x = new_x;
    y = new_y;
}
