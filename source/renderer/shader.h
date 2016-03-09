#ifndef HELIOS_SHADER_H
#define HELIOS_SHADER_H

#include <ray.h>
#include <light.h>
#include <material.h>


class Shader {
private:

    /**
     * Diffuse contribution calculation functions
     */
    float diffuse_lambert(const Vec3 &light_direction, const Vec3 &normal) const;

    /**
     * NDF functions
     */
    float ndf_ggx(const Vec3 &normal, const Vec3 &in_dir, const Vec3 &out_dir) const;

    /**
     * GSF functions
     */
    float gsf_cook_torance(const Vec3 &normal, const Vec3 &in_dir, const Vec3 &out_dir) const;

    /**
     * Fresnel functions
     */
    float fresnel_schlick_approximation(const Vec3 &normal, const Vec3 &in_dir, const Vec3 &out_dir) const;

public:
    float calculate_diffuse_contribution(const Vec3 &light_direction, const Vec3 &view_direction, HitPoint &hit_point,
                                         const Material &material) const;

    /**
     * Evaluate the B.R.D.F.
     */
    float calculate_specular_contribution(const Vec3 &normal, const Vec3 &in_dir, const Vec3 &out_dir, const Material &material);
};

#endif //HELIOS_SHADER_H
