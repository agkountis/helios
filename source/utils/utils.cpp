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

#include <sphere.h>
#include "utils.h"


void Utils::generate_sphere_flake(Scene *sc, const Material &mat, const Vec3 &pos, float radius, float scale, int iter)
{
    if(iter <= 0.0f)
        return;

    static Vec3 offs[] = {
            Vec3(1, 0, 0),
            Vec3(-1, 0, 0),
            Vec3(0, 1, 0),
            Vec3(0, -1, 0),
            Vec3(0, 0, 1),
            Vec3(0, 0, -1)
    };

    Sphere *sphere = new Sphere(pos, radius);
    sphere->material = mat;

    sc->add_drawable(sphere);

    for(auto v : offs) {

        float new_rad = radius * scale;
        Vec3 new_pos = pos + v * (radius + new_rad);

        generate_sphere_flake(sc, mat, new_pos, new_rad, scale, iter - 1);
    }
}
