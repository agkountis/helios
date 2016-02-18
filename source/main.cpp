#include <camera.h>
#include <drawable.h>
#include <sphere.h>
#include <scene.h>
#include <renderer.h>
#include <ray_tracer.h>
#include <plane.h>

static void sphere_flake(Scene * sc, const Material &mat, const Vec3 &pos, float radius, float scale, int iter)
{
    if(iter <= 0.0f)
        return;

    static Vec3 offs[] = {
            Vec3(1, 0, 0),
            Vec3(-1, 0, 0),
            Vec3(0, 1, 0),
            Vec3(0, -1, 0),
            Vec3(0, 0, 1),
            Vec3(0, 0, -1)
    };

    Sphere *sphere = new Sphere(pos, radius);
    sphere->material = mat;

    sc->add_drawable(sphere);

    for(auto v : offs) {

        float new_rad = radius * scale;
        Vec3 new_pos = pos + v * (radius + new_rad);

        sphere_flake(sc, mat, new_pos, new_rad, scale, iter - 1);
    }
}

int main(int argc, char **argv)
{
    Drawable *sphere = new Sphere(Vec3(0.0, 0.3f, 4.0f), 1);
    sphere->material.albedo = Vec3(0.93f, 0.93f, 0.93f);
    sphere->material.roughness = 0.4f;

    Drawable *plane = new Plane(Vec3(0, -2, 0), Vec3(0, 1, 0));
    plane->material.albedo = Vec3(0.88, 0.88, 0.88);
    plane->material.roughness = 0.1f;

    Camera camera;
    camera.set_position(Vec3(0.0, 0.0, 0.0f));
    camera.set_target(Vec3(0.0, 0.0f, 4));
    camera.set_fov(80.0f, Camera::CAM_FOV_DEGREES);

    Scene *scene = new Scene;
    sphere_flake(scene, sphere->material, Vec3(0, 0.6, 4.0f), 1, 0.4, 6);
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
    lt2->set_position(Vec3(-4.f, 4, 3));
    scene->add_light(lt2);

    Image image;
    image.create(4096, 2048);

    Renderer *renderer = new RayTracer(scene, image);

    renderer->initialize();
    renderer->render();

    image.save("test.ppm", Image::IMG_FMT_PPM);

    return 0;
}
