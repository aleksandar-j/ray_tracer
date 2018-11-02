#pragma once

#include "math_extension.hpp"
#include "vector.hpp"

class Camera {

public:
    Camera();
    Camera(const Vector& cam_position, const Vector& cam_direction,
           const double FOV_deg,
           const int scr_width, const int scr_height);

    Ray get_ray_on_pixel(const int x, const int y) const;
    void get_ray_on_pixel_next_horz(Ray& current_ray_out) const;

    Vector position;
    Vector direction;

    double FOV;

private:
    void initialize_view();

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

};
