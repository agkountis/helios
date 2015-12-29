#include "mat4.h"

void Mat4::translate(double x, double y, double z)
{
    matrix[0][3] += x;
    matrix[1][3] += y;
    matrix[2][3] += z;
}

void Mat4::translate(const Vec3 &position)
{
    matrix[0][3] += position.x;
    matrix[1][3] += position.y;
    matrix[2][3] += position.z;
}


void Mat4::scale(double x, double y, double z)
{
    matrix[0][0] *= x;
    matrix[1][1] *= y;
    matrix[2][2] *= z;
}

void Mat4::scale(const Vec3 &scale)
{
    matrix[0][0] *= scale.x;
    matrix[1][1] *= scale.y;
    matrix[2][2] *= scale.z;
}


void Mat4::set_identity()
{
    for(int i = 0 ; i < 4 ; i++) {
        for(int j = 0 ; j < 4 ; j++) {
            i == j ? matrix[i][j] = 1.0 : matrix[i][j] = 0.0;
        }
    }
}
