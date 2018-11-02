
#include "atmosphere.hpp"

Atmosphere::Atmosphere()
{
}
Atmosphere::Atmosphere(const Shape* atmosphere_shape,
                       const double light_dropoff_intensity, const double light_refraction_amount) 
    :
    atmosphere_shape(atmosphere_shape),
    light_dropoff_intensity(light_dropoff_intensity), light_refraction_amount(light_refraction_amount)
{
    this->density = (MAX_DOUBLE - this->light_dropoff_intensity * this->light_refraction_amount) / MAX_DOUBLE;
}
