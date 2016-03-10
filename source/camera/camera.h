/*
Helios-Ray - A powerful and highly configurable renderer
Copyright (C) 2016  Angelos Gkountis

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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

    void calculate_transformation();

    const Mat4 &get_transformation_matrix() const;
};

#endif //HELIOS_CAMERA_H
