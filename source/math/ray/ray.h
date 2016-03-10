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
