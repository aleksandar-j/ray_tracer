#pragma once

#include "math_extension.hpp"
#include "vector.hpp"

class Camera {

public:
    Vector position;
    Vector direction;

    double FOV;

    int screen_width;
    int screen_height;
    double screen_ratio;

    Vector camrect_leftdown;
    Vector camrect_leftup;
    Vector camrect_rightdown;
    Vector camrect_rightup;

    double camrect_width;
    double camrect_height;
    double camrect_width_per_pixel;
    double camrect_height_per_pixel;

    Vector camrect_xy_start_point;
    Ray camrect_width_ray;
    Ray camrect_height_ray;

    Camera() {}
    Camera(const Vector& cam_position, const Vector& cam_direction,
        const double FOV_deg,
        const int scr_width, const int scr_height) :
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

    // TODO: documentation
    Ray get_ray_on_pixel(const int x, const int y) const;

private:
    void initialize_view()
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

};
