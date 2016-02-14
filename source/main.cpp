#include <camera.h>
#include <drawable.h>
#include <sphere.h>
#include <scene.h>
#include <renderer.h>
#include <ray_tracer.h>
#include <plane.h>
#include <thread_pool.h>
#include <iostream>

int add(int i)
{
    i++;
    std::cout << i << std::endl;

    return i;
}

int main(int argc, char **argv)
{
    Drawable *sphere = new Sphere(Vec3(0.0, 0.0f, 4.0f), 1);
    sphere->material.diffuse_color = Vec3(0.8f, 0.0f, 0.0f);
    sphere->material.specular_color = Vec3(1.0f, 1.0f, 1.0f);
    sphere->material.shininess = 60.0f;
    sphere->material.reflectivity = 1.0;

    Drawable *sphere1 = new Sphere(Vec3(2.0, 0.1f, 4.0f), 0.5);
    sphere1->material.diffuse_color = Vec3(1.0f, 0.5f, 0.0f);
    sphere1->material.specular_color = Vec3(1.0f, 1.0f, 1.0f);
    sphere1->material.shininess = 60.0f;
    sphere1->material.reflectivity = 1.0;

    Drawable *sphere2 = new Sphere(Vec3(-2.0f, 0.1f, 4.0f), 0.5);
    sphere2->material.diffuse_color = Vec3(0.0f, 0.5f, 0.4f);
    sphere2->material.specular_color = Vec3(1.0f, 1.0f, 1.0f);
    sphere2->material.shininess = 60.0f;
    sphere2->material.reflectivity = 1.0;


    Drawable *plane = new Plane(Vec3(0.0f, -1.0f, 0.0f), Vec3(0, 1, 0));
    plane->material.diffuse_color = Vec3(0.0f, 0.0, 0.0);
    plane->material.specular_color = Vec3(0.0, 0.0, 0.0);
    plane->material.shininess = 100.0;
    plane->material.reflectivity = 1.0f;

    Drawable *plane2 = new Plane(Vec3(3.5f, 0.0f, 0.0f), Vec3(-1, 0, 0));
    plane2->material.diffuse_color = Vec3(0.0f, 0.0, 0.0);
    plane2->material.specular_color = Vec3(0.0, 0.0, 0.0);
    plane2->material.shininess = 200.0;
    plane2->material.reflectivity = 1.0f;

    Drawable *plane3 = new Plane(Vec3(0.0f, 0.0f, 5.0f), Vec3(0, 0, -1));
    plane3->material.diffuse_color = Vec3(0.0f, 0.0, 0.0);
    plane3->material.specular_color = Vec3(0.0, 0.0, 0.0);
    plane3->material.shininess = 200.0;
    plane3->material.reflectivity = 1.0f;

    Drawable *plane4 = new Plane(Vec3(-3.5f, 0.0f, 0.0f), Vec3(1, 0, 0));
    plane4->material.diffuse_color = Vec3(0.0f, 0.0, 0.0);
    plane4->material.specular_color = Vec3(0.0, 0.0, 0.0);
    plane4->material.shininess = 200.0;
    plane4->material.reflectivity = 1.0f;


    Camera camera;
    camera.set_position(Vec3(0.0, 0.0, 0.0f));
    camera.set_target(Vec3(0.0, 0.0f, 4));
    camera.set_fov(80.0f, Camera::CAM_FOV_DEGREES);

    Scene *scene = new Scene;
    scene->add_drawable(sphere1);
    scene->add_drawable(sphere);
    scene->add_drawable(sphere2);

    scene->add_drawable(plane);
    scene->add_drawable(plane2);
    scene->add_drawable(plane3);
    scene->add_drawable(plane4);

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
    image.create(4096, 2048);

    Renderer *renderer = new RayTracer(scene, image);

    renderer->initialize();
    renderer->render();

    image.save("test.ppm", Image::IMG_FMT_PPM);

    return 0;
}
