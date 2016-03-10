/*
Helios-Ray - A powerful and highly configurable renderer
Copyright (C) 2016  Angelos Gkountis

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <math.h>
#include <mat4.h>

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
