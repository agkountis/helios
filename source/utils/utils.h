#ifndef HELIOS_UTILS_H
#define HELIOS_UTILS_H

#include <scene.h>

class Utils {
public:
    Utils() = delete;

    static void generate_sphere_flake(Scene * sc, const Material &mat, const Vec3 &pos, float radius, float scale, int iter);
};

#endif //HELIOS_UTILS_H
