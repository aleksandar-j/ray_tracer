#pragma once

#include "math_extension.hpp"

#include <cinttypes>
#include <utility>
#include <limits>
#include <random>

class Vector {

public:
    double x;
    double y;
    double z;

    Vector() {}
    Vector(double x, double y) :
                x(x), y(y) 
    {
        this->z = 0;
    }
    Vector(double x, double y, double z) :
                x(x), y(y), z(z)
    {
    }

    bool operator==(const Vector& B) const;
    bool operator!=(const Vector& B) const;

    Vector operator+(const Vector& B) const;
    Vector operator+(const double B) const;
    Vector operator-(const Vector& B) const;
    Vector operator-(const double B) const;
    Vector operator*(const Vector& B) const;
    Vector operator*(const double B) const;
    Vector operator/(const Vector& B) const;
    Vector operator/(const double B) const;

    void operator+=(const Vector& B);
    void operator+=(const double B);
    void operator-=(const Vector& B);
    void operator*=(const double B);

    double magnitude() const;
    
    Vector get_unit_vector() const;
    void make_unit_vector();

};

double vec_dot_product(const Vector& A, const Vector& B);
double vec_distance(const Vector& A, const Vector& B);

class Ray : public Vector {

public:
    Vector origin;
    Vector direction;

    Ray() {}
    Ray(const Vector& origin, const Vector& direction) :
             origin(origin), direction(direction)
    {
        this->direction.make_unit_vector();
    }

};


class Color : public Vector {

public:
    uint32_t red;
    uint32_t green;
    uint32_t blue;

    Color() {}
    Color(const uint32_t red, const uint32_t green, const uint32_t blue) :
                red(red), green(green), blue(blue)
    {
    }
    Color(const uint32_t argb) 
    {
        this->red   = (argb & 0x00FF0000) >> 16;
        this->green = (argb & 0x0000FF00) >> 8;
        this->blue  = (argb & 0x000000FF) >> 0;
    }

    Color operator+(const Color& B) const;
    Color operator-(const Color& B) const;
    Color operator/(const double B) const;

    void operator+=(const Color& B);
    void operator-=(const Color& B);

    operator uint32_t() const;

};
#define BLACK { 0x0, 0x0, 0x0 }
#define WHITE { 0xFF, 0xFF, 0xFF }


class Shape {

public:
    virtual Vector ray_intersect(const Ray& ray) const = NULL;
    virtual Color color_at_vec(const Vector& point) const = NULL;

};

class Sphere : public Shape {

public:
    Sphere() {}
    Sphere(const Vector& center, const double radius) :
                center(center), radius(radius) 
    {
        color = WHITE;
    }
    Sphere(const Vector& center, const double radius, const Color& color) :
        center(center), radius(radius), color(color)
    {
    }

    virtual Vector ray_intersect(const Ray& ray) const;
    virtual Color color_at_vec(const Vector& point) const;

    Vector center;
    double radius;

    Color color;

};


class Camera : public Vector {

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
                screen_width(scr_width), screen_height(scr_height), screen_ratio(scr_width / scr_height)
    {
        // We can just spin the camera on 2D axis right now
        direction.z = 0;
        direction.make_unit_vector();

        // Make the rectangle that is the viewport
        initialize_view();
    }

    // TODO: documentation
    Ray get_ray_on_pixel(int x, int y);
    Ray get_ray_on_pixel_rand(int x, int y);

private:
    void initialize_view()
    {
        Vector rect_side1(cos(acos(direction.x) + (FOV / 2)),
                          sin(asin(direction.y) + (FOV / 2)), 0);
        rect_side1 *= 1 / (cos(FOV / 2));

        Vector rect_side2(cos(acos(direction.x) - (FOV / 2)),
                          sin(asin(direction.y) - (FOV / 2)), 0);
        rect_side2 *= 1 / (cos(FOV / 2));

        double rect_width = vec_distance(rect_side1, rect_side2);
        double rect_height = (1 / screen_ratio) * rect_width;

        camrect_leftup = rect_side1;
        camrect_leftup.z = position.z + rect_height / 2;
        camrect_rightup = rect_side2;
        camrect_rightup.z = position.z + rect_height / 2;

        camrect_leftdown = rect_side1;
        camrect_leftdown.z = position.z - rect_height / 2;
        camrect_rightdown = rect_side2;
        camrect_rightdown.z = position.z - rect_height / 2;

        camrect_width = vec_distance(camrect_leftdown, camrect_rightdown);
        camrect_height = vec_distance(camrect_leftdown, camrect_leftup);

        camrect_width_per_pixel = camrect_width / screen_width;
        camrect_height_per_pixel = camrect_height / screen_height;

        camrect_xy_start_point = camrect_leftup;
        camrect_width_ray = { camrect_xy_start_point, {camrect_rightup - camrect_xy_start_point} };
        camrect_height_ray = { camrect_xy_start_point, {camrect_leftdown - camrect_xy_start_point} };
    }

};
