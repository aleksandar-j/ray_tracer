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

    // Every shape has its own materiel type, default is full diffuse one
    Material material = {};

};

class Sphere : public Shape {

public:
    Sphere();
    Sphere(const Vector& center, const double radius);
    Sphere(const Vector& center, const double radius, 
           const Color& color);
    Sphere(const Vector& center, const double radius,
           const Color& color, const Material& material);

    virtual Intersect ray_intersect(const Ray& ray) const override;

    virtual bool point_in_object(const Vector& point) const override;

    virtual Ray normal_ray_at_point(const Vector& point) const override;
    virtual Color color_at_point(const Vector& point) const override;

    Vector center = {};
    double radius = 0.0;

    Color color = {};

};
