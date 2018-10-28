#pragma once

#include "math_extension.hpp"
#include "vector.hpp"
#include "intersect.hpp"

class Shape {

public:
    virtual Intersect ray_intersect(const Ray& ray) const = NULL;
    virtual Color color_at_point(const Vector& point, const Shape& object) const = NULL;
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

    virtual Intersect ray_intersect(const Ray& ray) const override;
    virtual Color color_at_point(const Vector& point, const Shape& object) const override;
    virtual Ray get_normal_ray_at_vec(const Vector& point) const override;

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

    virtual Intersect ray_intersect(const Ray& ray) const override;
    virtual Color color_at_point(const Vector& point, const Shape& object) const override;
    virtual Ray get_normal_ray_at_vec(const Vector& point) const override;

    Vector center;
    Vector height;
    Vector width;

    Color color;

};
