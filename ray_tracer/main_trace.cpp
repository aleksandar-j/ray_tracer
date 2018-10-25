
#include "main_trace.hpp"

#include "shapes.hpp"

void trace(int32_t* pixels, int w, int h)
{
    Camera cam{ {0, 0, 1}, {1, 1, 0}, 90.0, w, h };
    std::vector<Shape*> world;

    // World items
    //world.push_back(new Sphere{ {1, 1, -50}, 50 });
    world.push_back(new Sphere{ {3, 3, 1}, 1 });

    for (size_t y = 0; y < h; y++) {
        for (size_t x = 0; x < w; x++) {
            int32_t& current_pixel = pixels[y*w + x];

            // Draw here
            //x = 683; y = 384;
            Ray camera_ray = { cam.position, (cam.get_vec_on_pixel(x, y) - cam.position) };

            current_pixel = 0;

            for (auto& x : world) {
                bool intersect = x->ray_intersect(camera_ray);

                if (intersect) {
                    current_pixel = 0xFFFFFF;
                }
            }
        }
    }

}
