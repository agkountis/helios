#ifndef HELIOS_MATERIAL_H
#define HELIOS_MATERIAL_H

#include <vec3.h>

class Material {
public:
    Vec3 color;
    float transparency = 0.0;
    float reflectivity = 0.0;
    float emissivity = 0.0;
    float transmittance = 0.0;

    Material() = default;

    Material(const Vec3 &color, float transparency, float reflectivity, float emissivity, float transmittance)
            : color(color), transparency(transparency), reflectivity(reflectivity), emissivity(emissivity), transmittance(transmittance)
    { };
};

#endif //HELIOS_MATERIAL_H
