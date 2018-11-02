
#include "camera.hpp"

Camera::Camera()
{
}
Camera::Camera(const Vector& cam_position, const Vector& cam_direction,
               const double FOV_deg,
               const int scr_width, const int scr_height) 
    :
    position(cam_position), direction(cam_direction),
    FOV(deg_to_rad(FOV_deg)),
    screen_width(scr_width), screen_height(scr_height),
    screen_ratio((double)scr_width / (double)scr_height)
{
    // We can just spin the camera on 2D axis right now
    direction.z = 0;
    direction.make_unit_vector();

    // Make the rectangle that is the viewport
    initialize_view();
}

Ray Camera::get_ray_on_pixel(int x, int y) const
{
    Vector point_on_viewport = camrect_xy_start_point;

    point_on_viewport += camrect_width_ray.direction * (camrect_width_per_pixel * (x + 1)) -
                                    (camrect_width_per_pixel / 2);
    point_on_viewport += camrect_height_ray.direction * (camrect_height_per_pixel * (y + 1)) -
                                    (camrect_height_per_pixel / 2);

    return { this->position, point_on_viewport - this->position };
}

void Camera::get_ray_on_pixel_next_horz(Ray& current_ray_out) const
{
    current_ray_out.direction += camrect_width_ray.direction * camrect_width_per_pixel;
    current_ray_out.direction.make_unit_vector();
}

void Camera::initialize_view()
{
    Vector rect_side1(cos(acos(direction.x) + (FOV / 2)),
        sin(asin(direction.y) + (FOV / 2)), 0);
    rect_side1 *= 1 / (cos(FOV / 2));

    Vector rect_side2(cos(acos(direction.x) - (FOV / 2)),
        sin(asin(direction.y) - (FOV / 2)), 0);
    rect_side2 *= 1 / (cos(FOV / 2));

    camrect_width = vec_distance(rect_side1, rect_side2);
    camrect_height = (1 / screen_ratio) * camrect_width;

    camrect_width_per_pixel = camrect_width / screen_width;
    camrect_height_per_pixel = camrect_height / screen_height;

    camrect_leftup = rect_side1;
    camrect_leftup.z = position.z + camrect_height / 2.0;
    camrect_rightup = rect_side2;
    camrect_rightup.z = position.z + camrect_height / 2.0;

    camrect_leftdown = rect_side1;
    camrect_leftdown.z = position.z - camrect_height / 2.0;
    camrect_rightdown = rect_side2;
    camrect_rightdown.z = position.z - camrect_height / 2.0;

    camrect_xy_start_point = camrect_leftup;
    camrect_width_ray = { camrect_xy_start_point, {camrect_rightup - camrect_xy_start_point} };
    camrect_height_ray = { camrect_xy_start_point, {camrect_leftdown - camrect_xy_start_point} };
}
