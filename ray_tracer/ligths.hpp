#pragma once

#include "vector.hpp"
#include "shapes.hpp"

#include <limits>

class Light {

public:
    virtual double light_level_at_point(const std::vector<Shape*>& objects, const Intersect& intersect) const = NULL;

    // Value by which the color will be multiplied, 0-pitch black, 1-default colors, >1-brighter than normal
    double intensity = 1.0;

    // How many distance units before intensity is 0, if it drops linearly
    double intensity_dropoff_linear = std::numeric_limits<double>::max();

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
    PointLight(const Vector& center, const double intensity, const double intensity_dropoff_linear) :
        center(center)
    {
        this->intensity = intensity;
        this->intensity_dropoff_linear = intensity_dropoff_linear;
    }

    virtual double light_level_at_point(const std::vector<Shape*>& objects, const Intersect& intersect) const;

    Vector center;

};

class AmbientLight : public Light {

public:
    AmbientLight() 
    {
    }
    AmbientLight(const double intensity)
    {
        this->intensity = intensity;
    }
    
    virtual double light_level_at_point(const std::vector<Shape*>& objects, const Intersect& intersect) const;

};