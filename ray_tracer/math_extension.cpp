
#include "math_extension.hpp"

double deg_to_rad(double deg)
{
    return (deg * M_PI) / (180.0);
}

double rad_to_deg(double rad) 
{
    return (rad * 180.0) / (M_PI);
}
