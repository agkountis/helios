#include <camera.h>
#include <drawable.h>
#include <sphere.h>
#include <scene.h>
#include <renderer.h>
#include <ray_tracer.h>

int main(int argc, char **argv)
{
    Drawable *sphere = new Sphere(Vec3(0.0, 0.0, 4.0), 0.7);
    sphere->material.color = Vec3(1.0f, 0.0f, 0.0f);

    Drawable *sphere2 = new Sphere(Vec3(2, 0.0, 6.0), 0.3);
    sphere->material.color = Vec3(0.0f, 0.0f, 1.0f);

    Drawable *sphere3 = new Sphere(Vec3(0.0, -1.0f, 4.0), 0.5);
    sphere3->material.color = Vec3(0.0f, 1.0f, 0.0f);

    Drawable *sphere4 = new Sphere(Vec3(0.0, 1.0, 4.0), 0.3);
    sphere4->material.color = Vec3(1.0f, 1.0f, 0.0f);

    Camera camera;
    camera.set_fov(45.0f, Camera::CAM_FOV_DEGREES);
    //camera.set_position(Vec3(-5.0f, 0.0f, 0.0f));

    Scene *scene = new Scene;
    scene->add_drawable(sphere);
    scene->add_drawable(sphere2);
    scene->add_drawable(sphere3);
    scene->add_drawable(sphere4);
    scene->set_camera(camera);

    Light *lt = new Light;
    lt->set_color(Vec3(1.0f, 1.0f, 1.0f));
    lt->set_position(Vec3(0.0f, 5.0f, 0.0f));

    scene->add_light(lt);

    Image image;
    image.create(1024, 768);

    Renderer *renderer = new RayTracer(scene, image);

    renderer->render();

    image.save("test.ppm", Image::IMG_FMT_PPM);

    return 0;
}
