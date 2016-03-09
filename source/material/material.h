#ifndef HELIOS_MATERIAL_H
#define HELIOS_MATERIAL_H

#include <vec3.h>

enum DiffuseCalculationFunction {
    LAMBERT,
    OREN_NYAR
};

enum NormalDistributionFunction {
    GGX
};

enum GeometricShadowingFunction {
    COOK_TORRANCE
};

enum FresnelFunction {
    DEFAULT_FRESNEL,
    SCHLICK_APPROXIMATION
};

struct ShadingModel {

    DiffuseCalculationFunction diffuse_function;

    NormalDistributionFunction ndf;

    GeometricShadowingFunction gsf;

    FresnelFunction fresnel;

    ShadingModel() : diffuse_function(LAMBERT), ndf(GGX), gsf(COOK_TORRANCE), fresnel(SCHLICK_APPROXIMATION)
    { }

    ShadingModel(const DiffuseCalculationFunction &diffuse_function, const NormalDistributionFunction &ndf,
                 const GeometricShadowingFunction &gfs, const FresnelFunction &fresnel)
            : diffuse_function(diffuse_function), ndf(ndf), gsf(gfs), fresnel(fresnel)
    { }

};

class Material {
public:
    /**
     * Diffuse term.
     */
    Vec3 albedo = Vec3(1.0f, 1.0f, 1.0f);

    float roughness = 0.0f;

    /**
     * Index of refraction.
     */
    float ior = 0.0f;

    bool metallic = false;

    ShadingModel shading_model;

    Material() = default;

    Material(const Vec3 &albedo, float roughness, float ior, bool metallic, const ShadingModel &shading_model)
            : albedo(albedo), roughness(roughness), ior(ior), metallic(metallic), shading_model(shading_model)
    { }
};

#endif //HELIOS_MATERIAL_H
