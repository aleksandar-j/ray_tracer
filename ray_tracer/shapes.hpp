#pragma once

#include "math_extension.hpp"

class Vector {

public:
    Vector() {}
    Vector(double x, double y)
    {
        this->x = x;
        this->y = y;
        this->z = 0;
    }
    Vector(double x, double y, double z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    Vector operator+(Vector B);
    Vector operator-(Vector B);
    Vector operator*(Vector B);
    Vector operator/(Vector B);

    void operator*=(double B);

    double magnitude();
    
    Vector get_unit_vector();
    void make_unit_vector();

    double x;
    double y;
    double z;

};

double vec_dot_product(Vector A, Vector B);
double vec_distance(Vector A, Vector B);

class Ray : public Vector {

public:
    Ray() {}
    Ray(Vector start, Vector end) 
    {
        this->start = start;
        this->end = end;
    }

    Vector start, end;

};


class Shape {

public:
    Vector ray_intersect(Ray ray);

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

    Vector points[4];

};

class Sphere : public Shape {

public:
    Sphere() {}
    Sphere(Vector center, double radius) : 
                center(center), radius(radius) {}

    Vector ray_intersect(Ray ray);

    Vector center;
    double radius;

};


class Camera : public Rect, Vector {

public:
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

        Vector rect_side_1_up = rect_side1;
        rect_side_1_up.z = position.z + rect_height / 2;
        Vector rect_side_2_up = rect_side2;
        rect_side_2_up.z = position.z + rect_height / 2;

        Vector rect_side_1_down = rect_side1;
        rect_side_1_down.z = position.z - rect_height / 2;
        Vector rect_side_2_down = rect_side2;
        rect_side_2_down.z = position.z - rect_height / 2;
    
        view = { rect_side_1_up, rect_side_2_up, rect_side_1_down, rect_side_2_down };
    }

    // TODO: documentation
    Vector get_vec_on_pixel(int x, int y);

    Vector position;
    Vector direction;

    double FOV;

    int screen_width;
    int screen_height;
    double screen_ratio;

    Rect view;

};
