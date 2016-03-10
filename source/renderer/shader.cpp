#include "shader.h"

#ifdef _WIN32
#define _USE_MATH_DEFINES
#endif

#include <algorithm>
#include <iostream>

/* Private Functions ------------------------------------------------------------------------------ */

float Shader::diffuse_lambert(const Vec3 &light_direction, const Vec3 &normal) const
{
    return std::max(dot(light_direction, normal), 0.0f);
}

float Shader::ndf_ggx(const ShadingVariables &variables) const
{
    float a_sq = variables.roughness_squared * variables.roughness_squared;

    float denominator = (float) M_PI * ((variables.n_dot_h_squared * (a_sq - 1.0f) + 1.0f) *
                                        (variables.n_dot_h_squared * (a_sq - 1.0f) + 1.0f));

    if (denominator == 0.0f)
        denominator = 1e-6f;


    return a_sq / denominator;
}

float Shader::gsf_cook_torrance(const ShadingVariables &variables) const
{
    float term_a = (2.0f * variables.n_dot_h * variables.n_dot_v) / variables.v_dot_h;
    float term_b = (2.0f * variables.n_dot_h * variables.n_dot_l) / variables.v_dot_h;

    return std::min(std::min(1.0f, term_a), term_b);
}

float Shader::fresnel_schlick_approximation(const ShadingVariables &variables) const
{
    float reflectivity = 1.0f - variables.roughness;

    return reflectivity + (1.0f - reflectivity) * (float) pow(1.0f - (variables.v_dot_h), 5.0f);
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
    static const float min_roughness = 0.027f;
    float roughness = material.roughness < min_roughness ? min_roughness : material.roughness;

    float normal_distribution = 0.0f;
    float geometric_shadowing = 0.0f;
    float fresnel = 0.0f;

    ShadingVariables shading_variables;
    shading_variables.n_dot_v = dot(normal, out_dir);
    shading_variables.n_dot_l = dot(normal, in_dir);

    /**
     * if the incoming and outgoing direction are beneath the surface we can't have light transport.
     */
    if (shading_variables.n_dot_v <= 0.0f || shading_variables.n_dot_l <= 0.0f)
        return 0.0f;

    Vec3 h = (out_dir + in_dir).normalized();

    shading_variables.n_dot_h = std::max(dot(normal, h), 0.0f);
    shading_variables.n_dot_h_squared = shading_variables.n_dot_h * shading_variables.n_dot_h;
    shading_variables.v_dot_h = std::max(dot(out_dir, h), 1e-6f);

    shading_variables.roughness = roughness;
    shading_variables.roughness_squared = roughness * roughness;
    shading_variables.ior = material.ior;

    /**
     * Calculate the normal distribution based on the material's shading model.
     */
    switch (material.shading_model.ndf) {
        case GGX:
            normal_distribution = ndf_ggx(shading_variables);
            break;
    }

    /**
     * Calculate the geometric shadowing based on the material's shading model.
     */
    switch (material.shading_model.gsf) {
        case COOK_TORRANCE:
            geometric_shadowing = gsf_cook_torrance(shading_variables);
            break;
    }

    /**
     * Calculate the fresnel term based on the material's shading model.
     */
    switch (material.shading_model.fresnel) {
        case SCHLICK_APPROXIMATION:
            fresnel = fresnel_schlick_approximation(shading_variables);
            break;
        case DEFAULT_FRESNEL:
            break;
    }

    return (normal_distribution * fresnel * geometric_shadowing) /
           (4.0f * shading_variables.n_dot_l * shading_variables.n_dot_v);
}
