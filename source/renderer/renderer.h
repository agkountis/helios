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

#ifndef HELIOS_RENDERER_H
#define HELIOS_RENDERER_H


class Renderer {
protected:
    virtual Vec3 shade(const Ray &ray, HitPoint &hit_point, int iterations) = 0;

    virtual Vec3 trace_ray(const Ray &ray, int iterations) = 0;

    virtual void find_intersection(const Ray &ray, HitPoint &hit_point) = 0;

public:
    virtual ~Renderer() = default;

    virtual bool initialize() = 0;

    virtual void render() = 0;
};

#endif //HELIOS_RENDERER_H
