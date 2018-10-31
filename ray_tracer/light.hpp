#pragma once

#include "vector.hpp"

#include "shape.hpp"

struct ObjectList;

class Light {

public:
    virtual double light_level_at_point(const ObjectList& objects, const Intersect& intersect) const = 0;

    // Color which light emits
    Color light_color;

    // Value by which the color will be multiplied, 0-pitch black, 1-default colors, >1-brighter than normal
    double intensity = 1.0;

};

class PointLight : public Light {

public:
    PointLight() 
    {
    }
    PointLight(const Vector& center, const double intensity) :
        center(center)
    {
        this->intensity = intensity;
    }

    virtual double light_level_at_point(const ObjectList& objects, const Intersect& intersect) const;

    Vector center;

};
