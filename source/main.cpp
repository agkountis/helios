#include <mat4.h>
#include <stdio.h>
#include <iostream>

int main(int argc, char **argv)
{

    Mat4 mat;
    Mat4 mat2;

    mat.scale(Vec3(2.0, 2.0, 2.0));
    mat.translate(Vec3(3.0, 3.0, 3.0));
    mat2.scale(Vec3(3.0, 3.0, 3.0));

    Mat4 res = mat * mat2;

    std::cout << mat[3][3] << std::endl;
    return 0;
}