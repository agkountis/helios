#include <camera.h>
#include <drawable.h>
#include <sphere.h>
#include <scene.h>
#include <renderer.h>
#include <ray_tracer.h>
#include <plane.h>

int main(int argc, char **argv)
{
    Drawable *sphere = new Sphere(Vec3(0.0, 0.0f, 1.0f), 0.4);
    sphere->material.diffuse_color = Vec3(1.0f, 0.5f, 0.0f);
    sphere->material.specular_color = Vec3(1.0f, 1.0f, 1.0f);
    sphere->material.shininess = 60.0f;
    sphere->material.reflectivity = 1.0;


    Drawable *plane = new Plane(Vec3(0.0f, -5.0f, 0.0f), Vec3(0, 1, 0));
    plane->material.diffuse_color = Vec3(1.0f, 0.0, 0.0);
    plane->material.specular_color = Vec3(1.0, 1.0, 1.0);
    plane->material.shininess = 10.0;
    plane->material.reflectivity = 1.0;

    Drawable *plane1 = new Plane(Vec3(50.0f, 0.0, 0.0f), Vec3(-1, 0, 0));
    plane1->material.diffuse_color = Vec3(0.0f, 1.0, 0.0);
    plane1->material.specular_color = Vec3(1.0, 1.0, 1.0);
    plane1->material.shininess = 10.0;

    Drawable *plane2 = new Plane(Vec3(-50.0f, 0.0, 0.0f), Vec3(1, 0, 0));
    plane2->material.diffuse_color = Vec3(0.0f, 0.0, 1.0);
    plane2->material.specular_color = Vec3(1.0, 1.0, 1.0);
    plane2->material.shininess = 10.0;


    Camera camera;
    camera.set_position(Vec3(0.0, 0.0, 0.0));
    camera.set_fov(80.0f, Camera::CAM_FOV_DEGREES);

    Scene *scene = new Scene;
    scene->add_drawable(sphere);
//    scene->add_drawable(plane);
//    scene->add_drawable(plane1);
//    scene->add_drawable(plane2);

    scene->set_camera(camera);

    Light *lt;

    lt = new Light;
    lt->set_color(Vec3(1.0f, 1.0f, 1.0f));
    lt->set_position(Vec3(0.0f, 0.0, 0.0f));

    scene->add_light(lt);

    Image image;
    image.create(1024, 768);

    Renderer *renderer = new RayTracer(scene, image);

    renderer->render();

    image.save("test.ppm", Image::IMG_FMT_PPM);

    return 0;
}
