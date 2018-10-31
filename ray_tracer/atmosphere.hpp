#pragma once

#include "math_extension.hpp"

class Shape;

class Atmosphere {

public:
    Atmosphere()
    {
    }
    Atmosphere(const Shape* atmosphere_shape, 
               const double light_dropoff_intensity, const double light_refraction_amount) :
        atmosphere_shape(atmosphere_shape), 
        light_dropoff_intensity(light_dropoff_intensity), light_refraction_amount(light_refraction_amount)
    {
        this->density = (MAX_DOUBLE - this->light_dropoff_intensity * this->light_refraction_amount) / MAX_DOUBLE;
    }

    // Defines the weight by which we choose which atmosphere to pick when two clash 
    //  if two have the same weight, we pick at random
    // We create it from dropoff intensity and refraction amount
    double density = 0.0;

    // Shape in which any light refraction works
    const Shape* atmosphere_shape = nullptr;

    // How many distance units before strongest light intensity is 0
    double light_dropoff_intensity = MAX_DOUBLE;

    // This is how much light gets refracted and changes its path
    double light_refraction_amount = 0.5;

};
