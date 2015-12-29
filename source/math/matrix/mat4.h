#ifndef HELIOS_MAT4_H
#define HELIOS_MAT4_H

#include <vec3.h>

class Mat4 {
private:
    double matrix[4][4] = {{1.0, 0.0, 0.0, 0.0},
                           {0.0, 1.0, 0.0, 0.0},
                           {0.0, 0.0, 1.0, 0.0},
                           {0.0, 0.0, 0.0, 1.0}};

public:
    Mat4() = default;

    void translate(double x, double y, double z);

    void translate(const Vec3 &position);

    void scale(double x, double y, double z);

    void scale(const Vec3 &scale);

    void set_identity();
};

#endif //HELIOS_MAT4_H
