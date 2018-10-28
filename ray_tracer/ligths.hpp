#pragma once

#include "vector.hpp"
#include "shapes.hpp"

class Light {

public:
    virtual double light_level_at_point(const std::vector<Shape*>& objects, const Vector& point) const = NULL;

    // Value by which the color will be multiplied, 0-pitch black, 1-default colors, >1-brighter than normal
    double intensity;

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

    virtual double light_level_at_point(const std::vector<Shape*>& objects, const Vector& point) const;

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
    
    virtual double light_level_at_point(const std::vector<Shape*>& objects, const Vector& point) const;

};