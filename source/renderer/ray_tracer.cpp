#include <iostream>
#include <math.h>
#include "ray_tracer.h"

RayTracer::~RayTracer()
{
    delete scene;
}

void RayTracer::set_image(const Image &image)
{
    this->image = image;
}

void RayTracer::set_scene(const Scene *scene)
{
    this->scene = scene;
}

void RayTracer::render()
{
    if (!scene) {
        std::cerr << "RayTracer ERROR: Scene pointer is null." << std::endl;
        exit(1);
    }

    /**
     * Work with scan-lines for now.
     */
    for (int height = 0; height < image.get_height(); height++) {
        for (int width = 0; width < image.get_width(); width++) {
            //TODO: Create a primary ray. Trace it and get the final color.

        }
    }
}

void RayTracer::shade()
{

}

Vec3 RayTracer::trace_ray(const Ray &ray)
{
    return Vec3();
}


void RayTracer::find_intersection(const Ray &ray, HitPoint *hit_point)
{

}


Ray RayTracer::create_primary_ray(int pixel_x, int pixel_y) const
{
    int image_width = image.get_width();
    int image_height = image.get_height();

    float aspect = (float) image_width / (float) image_height;

    Camera camera = scene->get_camera();
    float camera_fov = camera.get_fov();
    Vec3 camera_target = camera.get_target();
    Vec3 camera_position = camera.get_position();

    Ray ray;

    /**
     * The ray origin is at 0 0 0 so we don't touch it.
     */
    ray.direction.x = (2.0 * (float) pixel_x / (float) image_width - 1.0) * aspect;
    ray.direction.y = 1.0 - 2.0 * (float) pixel_y / (float) image_height;
    ray.direction.z = 1.0 / tan(camera_fov / 2.0);

    Vec3 camera_dir = camera_target - camera_position;

    /**
     * Assume the up camera vector points towards the positive y axis.
     */
    Vec3 up(0.0f, 1.0f, 0.0f);
    Vec3 right = cross(up, camera_dir);

    camera_dir.normalize();

    /**
     * Compute the actual up vector.
     */
    up = cross(camera_dir, right);

    /**
     * Create the correct camera matrix.
     */
    Mat4 camera_matrix(right.x, up.x, camera_dir.x, camera_position.x,
                       right.y, up.y, camera_dir.y, camera_position.y,
                       right.z, up.z, camera_dir.z, camera_position.z,
                       0.0, 0.0, 0.0, 1.0f);

    ray.transform(camera_matrix);

    return ray;
}
