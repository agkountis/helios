#include <iostream>
#include <image.h>
#include <ray_tracer.h>

int main(int argc, char **argv)
{

    Image image(1024, 1024);
    Scene *sc = new Scene;

    Renderer *renderer = new RayTracer(sc, image);

    renderer->render();

    return 0;
}