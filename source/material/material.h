#ifndef HELIOS_MATERIAL_H
#define HELIOS_MATERIAL_H

#include <vec3.h>

class Material {
private:
    Vec3 color;
    float transparency = 0;
    float reflectivity = 0;

public:
    const Vec3 &get_color() const;

    float get_transparency() const;

    float get_reflectivity() const;
};

#endif //HELIOS_MATERIAL_H
