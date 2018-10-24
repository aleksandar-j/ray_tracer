
#include "main_trace.hpp"

#include "shapes.hpp"

void trace(int32_t* pixels, int w, int h)
{
    Camera cam{ {1, 1, 1}, {0, 1, 0}, 80 };
    std::vector<Shape> world;

    world.push_back(Sphere{ {2, 4, 3}, 2 });

    for (size_t y = 0; y < h; y++) {
        for (size_t x = 0; x < w; x++) {
            int32_t& current_pixel = pixels[y*w + x];

            // Draw here
            for (auto& x : world) {
                Vector intersect = x.ray_intersect();
            }
            current_pixel = y;
        }
    }

}
