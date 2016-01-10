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
