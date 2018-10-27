#pragma once

#include "math_extension.hpp"
#include "vector.hpp"

class Shape {

public:
    virtual Vector ray_intersect(const Ray& ray) const = NULL;
    virtual Color color_at_vec(const Vector& point) const = NULL;
    virtual Ray get_normal_ray_at_vec(const Vector& point) const = NULL;

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
    virtual Ray get_normal_ray_at_vec(const Vector& point) const;

    Vector center;
    double radius;

    Color color;

};

class Cube : public Shape {

public:
    Cube() {}
    Cube(const Vector& center, const Vector& width, const Vector& height) :
                center(center), width(width), height(height)
    {
    }
    Cube(const Vector& center, const Vector& width, const Vector& height, const Color& color) :
        center(center), width(width), height(height), color(color)
    {
    }

    virtual Vector ray_intersect(const Ray& ray) const;

    Vector center;
    Vector height;
    Vector width;

    Color color;

};
