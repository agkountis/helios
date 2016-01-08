#include <iostream>
#include <image.h>
#include <ray_tracer.h>

int main(int argc, char **argv)
{

//    Image image(1024, 1024);
//    Scene *sc = new Scene;
//
//    Renderer *renderer = new RayTracer(sc, image);
//
//    renderer->render();

    Mat4 mat;

    mat[0][0] = 1;
    mat[0][1] = 0;
    mat[0][2] = 0;
    mat[0][3] = 1;

    mat[1][0] = 0;
    mat[1][1] = 2;
    mat[1][2] = 1;
    mat[1][3] = 2;

    mat[2][0] = 2;
    mat[2][1] = 1;
    mat[2][2] = 0;
    mat[2][3] = 1;

    mat[3][0] = 2;
    mat[3][1] = 0;
    mat[3][2] = 1;
    mat[3][3] = 4;

    mat.transpose();

    mat.adjoint();

    return 0;
}