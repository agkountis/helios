#ifndef HELIOS_SCENE_H
#define HELIOS_SCENE_H

#include <vector>
#include <object.h>
#include <string>
#include <camera.h>
#include <collidable.h>

class Scene {
private:
    Camera camera;

    std::vector<Collidable *> objects;

public:
    void add_object(Collidable *object);

    Collidable *get_object(unsigned int idx) const;

    void add_objects(const std::vector<Collidable *> &objects);

    const std::vector<Collidable *> &get_objects() const;

    void set_camera(const Camera &camera);

    const Camera &get_camera() const;

    unsigned long get_onject_count() const;

    bool load(std::string path);
};

#endif //HELIOS_SCENE_H
