#pragma once

#include "vector.hpp"
#include "intersect.hpp"

#include "material.hpp"
#include "texture.hpp"

class Shape {

public:
    virtual Intersect ray_intersect(const Ray& ray) const = 0;
    
    virtual bool point_in_object(const Vector& point) const = 0;

    virtual Ray normal_ray_at_point(const Vector& point) const = 0;
    virtual Color color_at_point(const Vector& point) const = 0;

    Material material;

};

class Sphere : public Shape {

public:
    Sphere() {}
    Sphere(const Vector& center, const double radius) :
                center(center), radius(radius) 
    {
        this->color = WHITE;
        this->material = { 1.0, 0.0 };
    }
    Sphere(const Vector& center, const double radius, const Color& color) :
        center(center), radius(radius), color(color)
    {
        this->material = { 1.0, 0.0 };
    }
    Sphere(const Vector& center, const double radius, 
           const Color& color, const Material& material) :
        center(center), radius(radius), color(color)
    {
        this->material = material;
    }

    virtual Intersect ray_intersect(const Ray& ray) const override;

    virtual bool point_in_object(const Vector& point) const override;

    virtual Ray normal_ray_at_point(const Vector& point) const override;
    virtual Color color_at_point(const Vector& point) const override;

    Vector center;
    double radius;

    Color color;

};
