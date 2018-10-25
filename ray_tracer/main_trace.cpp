
#include "main_trace.hpp"
#include <vector>
#include <queue>
#include <ctime>

#include "shapes.hpp"

void trace(int32_t* pixels, int w, int h)
{


    Camera cam{ {0, 0, 1}, {1, 1, 0}, 90.0, w, h };
    std::vector<Shape*> world;

    // World items
    world.push_back(new Sphere{ {1, 1, -5000}, 5000, { 12, 200, 23 } });
    world.push_back(new Sphere{ {3, 3, 1}, 1 });

    for (size_t y = 0; y < h; y++) {
        for (size_t x = 0; x < w; x++) {
            int32_t& current_pixel = pixels[y*w + x];
            current_pixel = Color(BLACK);

            // Draw here
            Ray camera_ray = { cam.position, (cam.get_vec_on_pixel(x, y) - cam.position) };

            std::priority_queue<std::pair<double, Color>> intersections;

            for (auto& x : world) {
                intersections.push(x->ray_intersect(camera_ray));
            }

            current_pixel = intersections.top().second;
        }
    }

}
