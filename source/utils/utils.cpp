#include <sphere.h>
#include "utils.h"


void Utils::generate_sphere_flake(Scene *sc, const Material &mat, const Vec3 &pos, float radius, float scale, int iter)
{
    if(iter <= 0.0f)
        return;

    static Vec3 offs[] = {
            Vec3(1, 0, 0),
            Vec3(-1, 0, 0),
            Vec3(0, 1, 0),
            Vec3(0, -1, 0),
            Vec3(0, 0, 1),
            Vec3(0, 0, -1)
    };

    Sphere *sphere = new Sphere(pos, radius);
    sphere->material = mat;

    sc->add_drawable(sphere);

    for(auto v : offs) {

        float new_rad = radius * scale;
        Vec3 new_pos = pos + v * (radius + new_rad);

        generate_sphere_flake(sc, mat, new_pos, new_rad, scale, iter - 1);
    }
}
