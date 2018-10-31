#pragma once

#include "vector.hpp"

#include "shape.hpp"

#include <vector>
#include <limits>

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

class Atmosphere {

public:
    Atmosphere() 
    {
        this->atmosphere_volume = nullptr;
    }

    // Shape in which any light refraction works
    Shape* atmosphere_volume;

    // How many distance units before any light intensity is 0, if it drops linearly
    bool light_dropoff_linear = true;
    double light_dropoff_linear_intensity = std::numeric_limits<double>::max();

};