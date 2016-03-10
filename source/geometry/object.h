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

#ifndef HELIOS_OBJECT_H
#define HELIOS_OBJECT_H

#include <ray.h>

class Object {
protected:
    Vec3 position;

public:

    Object() = default;

    Object(const Vec3 &position) : position(position)
    { }

    virtual void set_position(const Vec3 &position)
    {
        this->position = position;
    }


    virtual const Vec3 &get_position() const
    {
        return position;
    }

    virtual ~Object() = default;
};

#endif //HELIOS_OBJECT_H
