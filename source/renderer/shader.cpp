#include "shader.h"

#ifdef _WIN32
#define _USE_MATH_DEFINES
#endif

#include <algorithm>

/* Private Functions ------------------------------------------------------------------------------ */

float Shader::diffuse_lambert(const Vec3 &light_direction, const Vec3 &normal) const
{
    return std::max(dot(light_direction, normal), 0.0f);
}

float Shader::ndf_ggx(const Vec3 &normal, const Vec3 &in_dir, const Vec3 &out_dir) const
{
    return 0;
}

float Shader::gsf_cook_torance(const Vec3 &normal, const Vec3 &in_dir, const Vec3 &out_dir) const
{
    return 0;
}

float Shader::fresnel_schlick_approximation(const Vec3 &normal, const Vec3 &in_dir, const Vec3 &out_dir) const
{
    return 0;
}

/* ------------------------------------------------------------------------------------------------ */

float Shader::calculate_diffuse_contribution(const Vec3 &light_direction, const Vec3 &view_direction,
                                             HitPoint &hit_point, const Material &material) const
{
    switch (material.shading_model.diffuse_function) {
        case LAMBERT:
            return diffuse_lambert(light_direction, hit_point.normal);
        case OREN_NYAR:
            break;
    }

    return 0;
}

float Shader::calculate_specular_contribution(const Vec3 &normal, const Vec3 &in_dir, const Vec3 &out_dir,
                                              const Material &material)
{
    float normal_distribution = 0.0f;
    float geometric_shadowing = 0.0f;
    float fresnel = 0.0f;

    float n_dot_v = dot(normal, out_dir);
    float n_dot_l = dot(normal, in_dir);

    /**
     * if the incoming and outgoing direction are beneath the surface we can't have light transport.
     */
    if (n_dot_v <= 0.0f || n_dot_l <= 0.0f)
        return 0.0f;

    /**
     * Calculate the normal distribution based on the material's shading model.
     */
    switch (material.shading_model.ndf) {
        case GGX:
            normal_distribution = ndf_ggx(normal, in_dir, out_dir);
            break;
    }

    /**
     * Calculate the geometric shadowing based on the material's shading model.
     */
    switch (material.shading_model.gsf) {
        case COOK_TORRANCE:
            geometric_shadowing = gsf_cook_torance(normal, in_dir, out_dir);
            break;
    }

    /**
     * Calculate the fresnel term based on the material's shading model.
     */
    switch (material.shading_model.fresnel) {
        case SCHLICK_APPROXIMATION:
            fresnel = fresnel_schlick_approximation(normal, in_dir, out_dir);
            break;
        case DEFAULT_FRESNEL:
            break;
    }

    return (normal_distribution * fresnel * geometric_shadowing) / (4.0f * n_dot_l * n_dot_v);
}
