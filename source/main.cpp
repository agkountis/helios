#include <camera.h>

int main(int argc, char **argv)
{
    Camera camera;
    camera.set_fov(45.0f, Camera::CAM_FOV_DEGREES);

    return 0;
}
