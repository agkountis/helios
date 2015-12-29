#include <mat4.h>
#include <stdio.h>

int main(int argc, char **argv)
{

    Mat4 mat;

    mat.translate(Vec3(10.0, 10.0, 0.0));
    mat.scale(Vec3(2.0, 2.0, 2.0));
    mat.scale(3.0, 3.0, 3.0);

    mat.set_identity();

    printf("foo");
    return 0;
}