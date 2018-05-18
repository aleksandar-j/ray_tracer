
#include "main_trace.hpp"

void trace(int32_t* pixels, int w, int h)
{

    for (size_t i = 0; i < w*h; i++) {
        pixels[i] = 0xFF00FF;
    }

}
