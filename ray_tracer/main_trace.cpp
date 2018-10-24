
#include "main_trace.hpp"

class Point {

public:
    Point() {}
    Point(double x, double y, double z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    double x;
    double y;
    double z;

};

void trace(int32_t* pixels, int w, int h)
{

    for (size_t y = 0; y < h; y++) {
        for (size_t x = 0; x < w; x++) {
            int32_t& current_pixel = pixels[y*w + x];

            current_pixel = y;
        }
    }

}
