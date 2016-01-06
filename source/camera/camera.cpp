#include "camera.h"


void Camera::set_position(const Vec3 &position)
{
    this->position = position;
}

const Vec3 &Camera::get_position() const
{
    return position;
}


void Camera::set_transformation(const Mat4 &transformation)
{
    this->transformation = transformation;
}

const Mat4 &Camera::get_transformation() const
{
    return transformation;
}
