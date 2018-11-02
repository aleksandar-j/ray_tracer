#pragma once

#include "math_extension.hpp"

class Shape;

class Atmosphere {

public:
    Atmosphere();
    Atmosphere(const Shape* atmosphere_shape,
               const double light_dropoff_intensity, const double light_refraction_amount);

    // Defines the weight by which we choose which atmosphere to pick when two clash 
    //  if two have the same weight, we pick at random
    // We create it from dropoff intensity and refraction amount
    double density = 0.0;

    // Shape in which any light refraction works
    const Shape* atmosphere_shape = nullptr;

    // How many distance units before strongest light intensity is 0
    double light_dropoff_intensity = MAX_DOUBLE;

    // This is how much light gets refracted and changes its path
    //  More precisely, it is the multiplier by which light intensity changes on 1 unit when not under direct light
    double light_refraction_amount = 0.5;

};
