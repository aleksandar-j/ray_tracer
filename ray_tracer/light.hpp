#pragma once

#include "vector.hpp"

#include "shape.hpp"

struct ObjectList;

class Light {

public:
    // Returns a value [0.0-1.0] that just tells how strong light is at the point, doesn't take intensity into account
    virtual double light_level_at_point(const ObjectList& world, const Intersect& intersect) const = 0;

    // Color which light emits at default brightness
    Color light_color = YELLOW;

    // Value by which the color will be multiplied, 0-pitch black, 0.5-default colors, 1-extreme brightness
    double intensity = 0.5;

};

class PointLight : public Light {

public:
    PointLight();
    PointLight(const Vector& center, const double intensity);
    PointLight(const Vector& center, const double intensity, const Color& light_color);

    virtual double light_level_at_point(const ObjectList& world, const Intersect& intersect) const;

    Vector center;

};
