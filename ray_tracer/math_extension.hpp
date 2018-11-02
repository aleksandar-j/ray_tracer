#pragma once

#define _USE_MATH_DEFINES
#include <cmath>
#include <limits>

#define MAX_DOUBLE (std::numeric_limits<double>::max())

double deg_to_rad(double deg);
double rad_to_deg(double rad);