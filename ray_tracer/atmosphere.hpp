#pragma once

class Shape;

#include <limits>

class Atmosphere {

public:
    Atmosphere()
    {
    }
    Atmosphere(const Shape* atmosphere_shape, const bool light_dropoff_linear, const double light_dropoff_linear_intensity) :
        atmosphere_shape(atmosphere_shape),
        light_dropoff_linear(light_dropoff_linear), light_dropoff_linear_intensity(light_dropoff_linear_intensity)
    {
        
    }

    // Defines the weight by which we choose which atmosphere to pick when two clash 
    //  if two have the same weight, we pick at random
    int density = 0;

    // Shape in which any light refraction works
    const Shape* atmosphere_shape = nullptr;

    // How many distance units before any light intensity is 0, if it drops linearly
    bool light_dropoff_linear = true;
    double light_dropoff_linear_intensity = std::numeric_limits<double>::max();

};