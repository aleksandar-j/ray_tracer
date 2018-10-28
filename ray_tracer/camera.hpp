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
    void initialize_view();

};
