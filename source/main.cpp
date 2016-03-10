/*
Helios-Ray - A powerful and highly configurable renderer
Copyright (C) 2016  Angelos Gkountis

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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
    Drawable *sphere = new Sphere(Vec3(2.0, 0.0f, 0.0f), 0.3);
    sphere->material.albedo = Vec3(1.000, 0.843f, 0.136);
    sphere->material.roughness = 0.3;
    sphere->material.metallic = true;

    Drawable *sphere2 = new Sphere(Vec3(1.5f, -0.0f, 0.0f), 0.1);
    sphere2->material.albedo = Vec3(1.000, 0.0f, 0.0);
    sphere2->material.roughness = 0.999f;
    sphere2->material.metallic = false;

    Drawable *plane_d = new Plane(Vec3(0, -0.3f, 0), Vec3(0, 1, 0));
    plane_d->material.albedo = Vec3(1.0, 1.0f, 1.0);
    plane_d->material.roughness = 0.8f;
    plane_d->material.metallic = false;

    Drawable *plane_b = new Plane(Vec3(0, 0, 6), Vec3(0, 0, -1));
    plane_b->material.albedo = Vec3(1.0, 1.0f, 1.0);
    plane_b->material.roughness = 1.0;
    plane_b->material.metallic = false;

    Drawable *plane_u = new Plane(Vec3(0, 7.0f, 0), Vec3(0, -1, 0));
    plane_u->material.albedo = Vec3(1.0, 1.0f, 1.0);
    plane_u->material.roughness = 1.0;
    plane_u->material.metallic = false;

    Drawable *plane_l = new Plane(Vec3(-3.5f, 0, 0), Vec3(1, 0, 0));
    plane_l->material.albedo = Vec3(1.0, 1.0f, 1.0);
    plane_l->material.roughness = 1.0;
    plane_l->material.metallic = false;

    Drawable *plane_r = new Plane(Vec3(3.5f, 0, 0), Vec3(-1, 0, 0));
    plane_r->material.albedo = Vec3(1.0, 0.1f, 0.1);
    plane_r->material.roughness = 0.4;
    plane_r->material.metallic = false;

    Drawable *plane_f = new Plane(Vec3(0, 0.0f, -3), Vec3(0, 0, 1));
    plane_f->material.albedo = Vec3(1.0, 1.0f, 1.0);
    plane_f->material.roughness = 1.0;
    plane_f->material.metallic = false;

    Camera camera;
    camera.set_position(Vec3(-0.1f, 0.0f, -1.0f));
    camera.set_target(Vec3(2.0, 0.0f, 0));
    camera.set_fov(50.0f, Camera::CAM_FOV_DEGREES);

    Scene *scene = new Scene;

    //Utils::generate_sphere_flake(scene, sphere->material, Vec3(0, 0.4, 0), 0.3, 0.4, 4);
    scene->add_drawable(sphere);
    scene->add_drawable(sphere2);
    scene->add_drawable(plane_d);
    scene->add_drawable(plane_b);
//    //scene->add_drawable(plane_u);
    scene->add_drawable(plane_l);
    scene->add_drawable(plane_r);
//    scene->add_drawable(plane_f);

    scene->set_camera(camera);

    Light *lt, *lt2;

    lt = new Light;
    lt->set_color(Vec3(1.0f, 1.0f, 1.0f));
    lt->set_position(Vec3(3.0f, 2.0, -6.0f));

    scene->add_light(lt);

    lt2 = new Light;
    lt2->set_color(Vec3(1.0, 1.0, 1.0));
    lt2->set_position(Vec3(-3.0, 6.0, 3.0));

    //scene->add_light(lt2);

    Image image;
    image.create(7680, 4320);

    Renderer *renderer = new RayTracer(scene, image);

    renderer->initialize();
    renderer->render();

    image.save("test.ppm", Image::IMG_FMT_PPM);

    return 0;
}
