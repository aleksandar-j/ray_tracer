#pragma once

#include "math_extension.hpp"

class Shape;

class Atmosphere {

public:
    Atmosphere()
    {
    }
    Atmosphere(const Shape* atmosphere_shape, const double density) :
        atmosphere_shape(atmosphere_shape), density(density)
    {
        light_dropoff_intensity = MAX_DOUBLE - (MAX_DOUBLE * density);
    }

    // Defines the weight by which we choose which atmosphere to pick when two clash 
    //  if two have the same weight, we pick at random
    // It also defines how much light we lose during travel, defining light_dropoff_intensity
    //  density of 0 - gives infinite dropoff intensity, density of 1 makes it 0
    double density = 0.0;

    // Shape in which any light refraction works
    const Shape* atmosphere_shape = nullptr;

    // How many distance units before strongest light intensity is 0
    double light_dropoff_intensity = MAX_DOUBLE;

};
