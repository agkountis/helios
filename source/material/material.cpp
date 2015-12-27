#include "material.h"


const Vec3 &Material::get_color() const
{
    return color;
}

float Material::get_transparency() const
{
    return transparency;
}

float Material::get_reflectivity() const
{
    return reflectivity;
}
