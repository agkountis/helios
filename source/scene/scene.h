#ifndef HELIOS_SCENE_H
#define HELIOS_SCENE_H

#include <vector>
#include <object.h>
#include <string>

class Scene {
private:
    std::vector<Object*> objects;

public:
    void add_object(Object *object);

    Object *get_object(unsigned int idx) const;

    const std::vector<Object*> &get_objects() const;

    bool load(std::string path);
};

#endif //HELIOS_SCENE_H
