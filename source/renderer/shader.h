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

#ifndef HELIOS_SHADER_H
#define HELIOS_SHADER_H

#include <ray.h>
#include <light.h>
#include <material.h>

struct ShadingVariables {
    float n_dot_h = 0.0f;
    float n_dot_h_squared = 0.0f;
    float n_dot_v = 0.0f;
    float n_dot_l = 0.0f;
    float v_dot_h = 0.0f;
    float roughness = 0.0f;
    float roughness_squared = 0.0f;
    float ior = 0.0f;
};

class Shader {
private:

    /**
     * Diffuse contribution calculation functions
     */
    float diffuse_lambert(const Vec3 &light_direction, const Vec3 &normal) const;

    float diffuse_oren_nayar(const Vec3 &light_direction, const Vec3 &view_direction, const HitPoint &hit_point) const;

    /**
     * NDF functions
     */
    float ndf_ggx(const ShadingVariables &variables) const;

    /**
     * GSF functions
     */
    float gsf_cook_torrance(const ShadingVariables &variables) const;

    /**
     * Fresnel functions
     */
    float fresnel_schlick_approximation(const ShadingVariables &variables) const;

public:
    float calculate_diffuse_contribution(const Vec3 &light_direction, const Vec3 &view_direction, HitPoint &hit_point,
                                         const Material &material) const;

    /**
     * Evaluate the B.R.D.F.
     */
    float calculate_specular_contribution(const Vec3 &normal, const Vec3 &in_dir, const Vec3 &out_dir, const Material &material);
};

#endif //HELIOS_SHADER_H
