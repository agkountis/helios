#ifndef HELIOS_CAMERA_H
#define HELIOS_CAMERA_H

#include <vec3.h>
#include <mat4.h>
#include <object.h>

class Camera : public Object {
private:
    Mat4 transformation;

public:
    Camera() = default;

    Camera(const Vec3 &position) : Object(position)
    { }

    void set_position(const Vec3 &position);

    const Vec3 &get_position() const;

    void set_transformation(const Mat4 &transformation);

    const Mat4 &get_transformation() const;
};

#endif //HELIOS_CAMERA_H
