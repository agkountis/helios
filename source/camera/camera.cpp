#include <math.h>
#include "camera.h"


void Camera::set_target(const Vec3 &target)
{
    this->target = target;
}

const Vec3 &Camera::get_target() const
{
    return target;
}

void Camera::set_fov(float fov, CameraFovType fov_type)
{
    switch (fov_type) {
        case CAM_FOV_RADIANS:
            this->fov = fov;
            break;
        case CAM_FOV_DEGREES:
            this->fov = (float) M_PI * fov / 180.0f;
    }
}

float Camera::get_fov() const
{
    return fov;
}

const Mat4 &Camera::get_transformation_matrix()
{
    Vec3 camera_dir = target - position;

    camera_dir.normalize();

    /**
     * Assume the up camera vector points towards the positive y axis.
     */
    Vec3 up(0.0f, 1.0f, 0.0f);
    Vec3 right = cross(up, camera_dir);
    right.normalize();

    /**
     * Compute the actual up vector.
     */
    up = cross(camera_dir, right);
    up.normalize();

    /**
     * Create the correct camera matrix.
     */
    //TODO: FIX THE LOOK-AT MATRIX.
    transformation = Mat4(right.x, right.y, right.z, 0,
                          up.x, up.y, up.z, 0,
                          camera_dir.x, camera_dir.y, camera_dir.z, 0,
                          0, 0, 0, 1);

    transformation.translate(position);

    return transformation;
}
