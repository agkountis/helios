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

#ifndef HELIOS_SCENE_H
#define HELIOS_SCENE_H

#include <vector>
#include <object.h>
#include <string>
#include <camera.h>
#include <drawable.h>
#include <light.h>


class Scene {
private:
    Camera camera;

    std::vector<Drawable *> drawables;

    std::vector<Light *> lights;

    void destroy_drawables();

    void destroy_lights();

public:

    ~Scene();

    void set_camera(const Camera &camera);

    const Camera &get_camera() const;

    void add_drawable(Drawable *object);

    Drawable *get_drawable(unsigned int index) const;

    void set_drawables(const std::vector<Drawable *> &objects);

    const std::vector<Drawable *> &get_drawables() const;

    unsigned long get_drawable_count() const;

    void add_light(Light *light);

    Light *get_light(unsigned int index) const;

    void set_lights(const std::vector<Light *> &lights);

    const std::vector<Light *> &get_lights() const;

    unsigned long get_lights_count() const;

    bool load(std::string path);
};

#endif //HELIOS_SCENE_H
