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

#ifndef HELIOS_LIGHT_H
#define HELIOS_LIGHT_H

#include <object.h>

class Light : public Object {
private:
    Vec3 color;

public:
    Light() = default;

    Light(const Vec3 &position, const Vec3 &color) : Object(position), color(color)
    { }

    void set_color(const Vec3 &color)
    {
        this->color = color;
    }

    const Vec3 &get_color() const
    {
        return color;
    }
};

#endif //HELIOS_LIGHT_H
