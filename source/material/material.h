#ifndef HELIOS_MATERIAL_H
#define HELIOS_MATERIAL_H

#include <vec3.h>

class Material {
public:
    Vec3 diffuse_color = Vec3(1.0f, 1.0f, 1.0f);
    Vec3 specular_color = Vec3(1.0f, 1.0f, 1.0f);
    float shininess = 0.0;
    float transparency = 0.0;
    float reflectivity = 0.0;
    float emissivity = 0.0;
    float transmittance = 0.0;

    Material() = default;

    Material(const Vec3 &diffuse_color, const Vec3 &specular_color, float shininess, float transparency,
             float reflectivity,
             float emissivity, float transmittance)
            : diffuse_color(diffuse_color), specular_color(specular_color), shininess(shininess),
              transparency(transparency),
              reflectivity(reflectivity), emissivity(emissivity), transmittance(transmittance)
    { };
};

#endif //HELIOS_MATERIAL_H
