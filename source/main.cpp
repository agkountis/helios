#include <camera.h>
#include <drawable.h>
#include <sphere.h>
#include <scene.h>
#include <renderer.h>
#include <ray_tracer.h>

int main(int argc, char **argv)
{
    Drawable *sphere = new Sphere(Vec3(0.0, -0.5f, 4.0f), 1.7);
    sphere->material.diffuse_color = Vec3(1.0f, 0.5f, 0.0f);
    sphere->material.specular_color = Vec3(1.0f, 1.0f, 1.0f);
    sphere->material.shininess = 60.0f;

    Drawable *sphere1 = new Sphere(Vec3(0.0f, 2.0, 4.0f), 0.6);
    sphere1->material.diffuse_color = Vec3(1.0f, 0.0f, 0.0f);
    sphere1->material.specular_color = Vec3(1.0f, 1.0f, 1.0f);
    sphere1->material.shininess = 30.0f;

    Drawable *sphere2 = new Sphere(Vec3(-0.4f, -0.1f, 2.0f), 0.2);
    sphere2->material.diffuse_color = Vec3(0.0f, 0.0f, 1.0f);
    sphere2->material.specular_color = Vec3(1.0f, 1.0f, 1.0f);
    sphere2->material.shininess = 10.0f;

    Camera camera;
    camera.set_fov(90.0f, Camera::CAM_FOV_DEGREES);

    Scene *scene = new Scene;
    scene->add_drawable(sphere);
    scene->add_drawable(sphere1);
    scene->add_drawable(sphere2);
    scene->set_camera(camera);

    Light *lt = new Light;
    lt->set_color(Vec3(1.0f, 1.0f, 1.0f));
    lt->set_position(Vec3(0.0f, 4.0f, 7.0f));

    scene->add_light(lt);

    lt = new Light;
    lt->set_color(Vec3(1.0f, 1.0f, 1.0f));
    lt->set_position(Vec3(-1.0f, -2.f, 0.0f));

    scene->add_light(lt);

    lt = new Light;
    lt->set_color(Vec3(1.0f, 1.0f, 1.0f));
    lt->set_position(Vec3(2.0f, 0.0f, -5.0f));
    scene->add_light(lt);

    Image image;
    image.create(1024, 1024);

    Renderer *renderer = new RayTracer(scene, image);

    renderer->render();

    image.save("test.ppm", Image::IMG_FMT_PPM);

    return 0;
}
