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
