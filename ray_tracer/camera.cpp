
#include "camera.hpp"

Ray Camera::get_ray_on_pixel(int x, int y)
{
    Vector point_on_viewport = camrect_xy_start_point;

    point_on_viewport += camrect_width_ray.direction * (camrect_width_per_pixel * (x + 1)) -
        (camrect_width_per_pixel / 2);
    point_on_viewport += camrect_height_ray.direction * (camrect_height_per_pixel * (y + 1)) -
        (camrect_height_per_pixel / 2);

    return { this->position, point_on_viewport - this->position };
}

Ray Camera::get_ray_on_pixel_rand(int x, int y)
{
    Vector point_on_viewport = camrect_xy_start_point;

    double rand_x = (double)(rand() % (int)(camrect_width_per_pixel * 10000)) / 10000.0;
    double rand_y = (double)(rand() % (int)(camrect_width_per_pixel * 10000)) / 10000.0;

    point_on_viewport += camrect_width_ray.direction * (camrect_width_per_pixel * (x + 1)) - rand_x;
    point_on_viewport += camrect_height_ray.direction * (camrect_height_per_pixel * (y + 1)) - rand_y;

    return { this->position, point_on_viewport - this->position };
}
