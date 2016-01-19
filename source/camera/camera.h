#ifndef HELIOS_CAMERA_H
#define HELIOS_CAMERA_H

#include <vec3.h>
#include <mat4.h>
#include <object.h>

class Camera : public Object {
private:
    Vec3 target = Vec3(0.0f, 0.0f, 1.0f);

    Mat4 transformation;

    /**
     * The Field of View in radians.
     */
    float fov = 0;

public:
    Camera() = default;

    Camera(const Vec3 &position) : Object(position)
    { }

    enum CameraFovType {
        CAM_FOV_RADIANS,
        CAM_FOV_DEGREES
    };

    void set_target(const Vec3 &target);

    const Vec3 &get_target() const;

    void set_fov(float fov, CameraFovType fov_type);

    float get_fov() const;

    const Mat4 &get_transformation_matrix();
};

#endif //HELIOS_CAMERA_H
