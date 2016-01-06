#include "scene.h"


void Scene::add_object(Object *object)
{
    objects.push_back(object);
}

Object *Scene::get_object(unsigned int idx) const
{
    return objects[idx];
}

const std::vector<Object *> &Scene::get_objects() const
{
    return objects;
}

bool Scene::load(std::string path)
{
    return false;
}
