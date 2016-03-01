#include <camera.h>
#include <drawable.h>
#include <sphere.h>
#include <scene.h>
#include <renderer.h>
#include <ray_tracer.h>
#include <plane.h>
#include <utils.h>


int main(int argc, char **argv)
{
    Drawable *sphere = new Sphere(Vec3(0.0, 0.0f, 4.0f), 1);
    sphere->material.albedo = Vec3(1.000, 0.843f, 0.136);
    sphere->material.roughness = 0.3f;
    sphere->material.metallic = true;

    Drawable *plane = new Plane(Vec3(0, -1.5f, 0), Vec3(0, 1, 0));
    plane->material.albedo = Vec3(0.1, 0.1f, 0.1);
    plane->material.roughness = 0.2f;
    plane->material.metallic = true;

    Camera camera;
    camera.set_position(Vec3(0.0f, 0.0f, -2.0f));
    camera.set_target(Vec3(0.0, 0.0f, 4));
    camera.set_fov(45.0f, Camera::CAM_FOV_DEGREES);

    Scene *scene = new Scene;

    Utils::generate_sphere_flake(scene, sphere->material, Vec3(0, 0.6, 4.0f), 1, 0.4, 4);
    //scene->add_drawable(sphere);
    scene->add_drawable(plane);

    scene->set_camera(camera);

    Light *lt;

    lt = new Light;
    lt->set_color(Vec3(1.0f, 1.0f, 1.0f));
    lt->set_position(Vec3(0.0f, 5.0, 1.0f));

    scene->add_light(lt);

    Light *lt2 = new Light;
    lt2->set_color(Vec3(1, 1, 1));
    lt2->set_position(Vec3(-4.f, 1, 3));
    scene->add_light(lt2);

    Image image;
    image.create(1024, 768);

    Renderer *renderer = new RayTracer(scene, image);

    renderer->initialize();
    renderer->render();

    image.save("test.ppm", Image::IMG_FMT_PPM);

    return 0;
}
