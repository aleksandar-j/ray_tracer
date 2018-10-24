
#include "math_extension.hpp"

double deg_to_rad(double deg)
{
    return (deg * 2 * M_PI) / (360);
}

double rad_to_deg(double rad) 
{
    return (rad * 360) / (2 * M_PI);
}
