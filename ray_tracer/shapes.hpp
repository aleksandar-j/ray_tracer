#pragma once

#include "math_extension.hpp"

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

    bool operator==(const Vector B) const;
    bool operator!=(const Vector B) const;

    Vector operator+(const Vector B) const;
    Vector operator+(const double B) const;
    Vector operator-(const Vector B) const;
    Vector operator-(const double B) const;
    Vector operator*(const Vector B) const;
    Vector operator*(const double B) const;
    Vector operator/(const Vector B) const;
    Vector operator/(const double B) const;

    void operator+=(const Vector B);
    void operator+=(const double B);
    void operator-=(const Vector B);
    void operator*=(const double B);

    double magnitude() const;
    
    Vector get_unit_vector() const;
    void make_unit_vector();

};

double vec_dot_product(const Vector A, const Vector B);
double vec_distance(const Vector A, const Vector B);

class Ray : public Vector {

public:
    Vector origin;
    Vector direction;

    Ray() {}
    Ray(Vector origin, Vector direction) : 
             origin(origin), direction(direction)
    {
        this->direction.make_unit_vector();
    }

};


class Shape {

public:
    virtual bool ray_intersect(const Ray ray) const = NULL;

};

class Rect : public Shape {

public:
    Rect() {}
    Rect(Vector A, Vector B, Vector C, Vector D) 
    {
        points[0] = A;
        points[1] = B;
        points[2] = C;
        points[3] = D;
    }

    virtual bool ray_intersect(const Ray ray) const;

    Vector points[4];

};

class Sphere : public Shape {

public:
    Sphere() {}
    Sphere(Vector center, double radius) : 
                center(center), radius(radius) {}

    virtual bool ray_intersect(const Ray ray) const;

    Vector center;
    double radius;

};


class Camera : public Rect, Vector {

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
    Camera(Vector cam_position, Vector cam_direction, double FOV_deg, int scr_width, int scr_height) : 
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
    Vector get_vec_on_pixel(int x, int y);

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
