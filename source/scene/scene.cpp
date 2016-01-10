#include "scene.h"


void Scene::add_object(Collidable *object)
{
    objects.push_back(object);
}

Collidable *Scene::get_object(unsigned int idx) const
{
    return objects[idx];
}

void Scene::add_objects(const std::vector<Collidable *> &objects)
{
    this->objects = objects;
}

const std::vector<Collidable *> &Scene::get_objects() const
{
    return objects;
}


void Scene::set_camera(const Camera &camera)
{
    this->camera = camera;
}

const Camera &Scene::get_camera() const
{
    return camera;
}

bool Scene::load(std::string path)
{
    return false;
}
