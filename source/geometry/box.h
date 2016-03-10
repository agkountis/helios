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

#ifndef HELIOS_BOX_H
#define HELIOS_BOX_H

#include "drawable.h"

class Box : public Drawable {
protected:
    double length;
    double width;
    double height;

public:
    Box() = default;

    Box(const Vec3 &position, double length, double width, double height)
            : Drawable(position), length(length), width(width), height(height)
    { }

    bool intersect(const Ray &ray, HitPoint *hit_point);
};

#endif //HELIOS_BOX_H
