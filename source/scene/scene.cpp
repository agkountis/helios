#include <iostream>
#include "scene.h"

/* Private Functions -------------------------------------------------------- */

void Scene::destroy_drawables()
{
    if(drawables.empty())
        return;

    for(Drawable *drawable : drawables) {
        delete drawable;
    }
}

void Scene::destroy_lights()
{
    if(lights.empty())
        return;

    for(Light *light : lights) {
        delete light;
    }
}

/* -------------------------------------------------------------------------- */

void Scene::set_camera(const Camera &camera)
{
    this->camera = camera;
}

const Camera &Scene::get_camera() const
{
    return camera;
}

void Scene::add_drawable(Drawable *drawable)
{
    drawables.push_back(drawable);
}

Drawable *Scene::get_drawable(unsigned int idx) const
{
    if(drawables.empty()) {
        std::cerr << "Drawable object array is empty! Returning NULL." << std::endl;
        return nullptr;
    }

    return drawables[idx];
}

void Scene::set_drawables(const std::vector<Drawable *> &drawables)
{
    destroy_drawables();
    this->drawables = drawables;
}

const std::vector<Drawable *> &Scene::get_drawables() const
{
    return drawables;
}

unsigned long Scene::get_drawable_count() const
{
    return drawables.size();
}

void Scene::add_light(Light *light)
{
    lights.push_back(light);
}

Light *Scene::get_light(unsigned int index) const
{
    if(lights.empty()) {
        std::cerr << "Lights array is empty! Returning NULL." << std::endl;
        return nullptr;
    }

    return lights[index];
}

void Scene::set_lights(const std::vector<Light *> &lights)
{
    destroy_lights();
    this->lights = lights;
}

const std::vector<Light *> &Scene::get_lights() const
{
    return lights;
}

unsigned long Scene::get_lights_count() const
{
    return lights.size();
}

bool Scene::load(std::string path)
{
    return false;
}
