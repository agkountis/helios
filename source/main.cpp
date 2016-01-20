#include <camera.h>
#include <drawable.h>
#include <sphere.h>
#include <scene.h>
#include <renderer.h>
#include <ray_tracer.h>
#include <plane.h>

int main(int argc, char **argv)
{
    Drawable *sphere = new Sphere(Vec3(0.0, 0.0f, 4.0f), 1);
    sphere->material.diffuse_color = Vec3(0.2f, 0.5f, 0.0f);
    sphere->material.specular_color = Vec3(1.0f, 1.0f, 1.0f);
    sphere->material.shininess = 60.0f;
    sphere->material.reflectivity = 1.0;

    Drawable *sphere1 = new Sphere(Vec3(2.0, 0.1f, 4.0f), 0.5);
    sphere1->material.diffuse_color = Vec3(1.0f, 0.5f, 0.0f);
    sphere1->material.specular_color = Vec3(1.0f, 1.0f, 1.0f);
    sphere1->material.shininess = 60.0f;
    sphere1->material.reflectivity = 1.0;


    Drawable *plane = new Plane(Vec3(0.0f, -1.0f, 0.0f), Vec3(0, 1, 0));
    plane->material.diffuse_color = Vec3(0.3f, 0.1, 0.2);
    plane->material.specular_color = Vec3(1.0, 1.0, 1.0);
    plane->material.shininess = 100.0;
    plane->material.reflectivity = 1.0f;

    Camera camera;
    camera.set_position(Vec3(0.0, 0.0, 0.0f));
    camera.set_target(Vec3(0.0, 0.0f, 4));
    camera.set_fov(80.0f, Camera::CAM_FOV_DEGREES);

    Scene *scene = new Scene;
    scene->add_drawable(sphere1);
    scene->add_drawable(sphere);

    scene->add_drawable(plane);

    scene->set_camera(camera);

    Light *lt;

    lt = new Light;
    lt->set_color(Vec3(1.0f, 1.0f, 1.0f));
    lt->set_position(Vec3(0.0f, 5.0, 1.0f));

    scene->add_light(lt);

    Light *lt2 = new Light;
    lt2->set_color(Vec3(1, 1, 1));
    lt2->set_position(Vec3(-3.f, 1, 3));
    scene->add_light(lt2);

    Image image;
    image.create(1024, 768);

    Renderer *renderer = new RayTracer(scene, image);

    renderer->render();

    image.save("test.ppm", Image::IMG_FMT_PPM);

    return 0;
}
