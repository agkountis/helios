#include <camera.h>
#include <collidable.h>
#include <sphere.h>
#include <scene.h>
#include <renderer.h>
#include <ray_tracer.h>

int main(int argc, char **argv)
{
    Collidable *sphere = new Sphere(Vec3(0.0, 0.0, 4.0), 0.7);
    Collidable *sphere2 = new Sphere(Vec3(2, 0.0, 6.0), 0.3);
    Collidable *sphere3 = new Sphere(Vec3(0.0, -1.0, 4.0), 0.5);
    Collidable *sphere4 = new Sphere(Vec3(0.0, 1.0, 4.0), 0.3);

    Camera camera;
    camera.set_fov(45.0f, Camera::CAM_FOV_DEGREES);

    Scene *scene = new Scene;
    scene->add_object(sphere);
    scene->add_object(sphere2);
    scene->add_object(sphere3);
    scene->add_object(sphere4);
    scene->set_camera(camera);

    Image image;
    image.create(1024, 768);

    Renderer *renderer = new RayTracer(scene, image);

    renderer->render();

    image.save("test.ppm", Image::IMG_FMT_PPM);

    return 0;
}
