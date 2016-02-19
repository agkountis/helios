#ifndef HELIOS_MATERIAL_H
#define HELIOS_MATERIAL_H

#include <vec3.h>

class Material {
public:
    /**
     * Diffuse term.
     */
    Vec3 albedo = Vec3(1.0f, 1.0f, 1.0f);

    float roughness = 0.0f;

    float ior = 0.0f;

    bool metallic = false;

    Material() = default;

    Material(const Vec3 &albedo, float roughness, float ior, bool metallic) : albedo(albedo), roughness(roughness),
                                                                              ior(ior), metallic(metallic)
    { }
};

#endif //HELIOS_MATERIAL_H
