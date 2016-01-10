#include <camera.h>
#include <collidable.h>
#include <sphere.h>
#include <scene.h>
#include <renderer.h>
#include <ray_tracer.h>

int main(int argc, char **argv)
{
    Collidable *sphere = new Sphere(Vec3(0.0, 0.0, 4.0), 1.0);

    Camera camera;
    camera.set_fov(45.0f, Camera::CAM_FOV_DEGREES);

    Scene *scene = new Scene;
    scene->add_object(sphere);
    scene->set_camera(camera);

    Image image(1024, 1024);

    Renderer *renderer = new RayTracer(scene, image);

    renderer->render();

    return 0;
}
