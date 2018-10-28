
#include "camera.hpp"

Ray Camera::get_ray_on_pixel(int x, int y) const
{
    Vector point_on_viewport = camrect_xy_start_point;

    point_on_viewport += camrect_width_ray.direction * (camrect_width_per_pixel * (x + 1)) -
                                    (camrect_width_per_pixel / 2);
    point_on_viewport += camrect_height_ray.direction * (camrect_height_per_pixel * (y + 1)) -
                                    (camrect_height_per_pixel / 2);

    return { this->position, point_on_viewport - this->position };
}
