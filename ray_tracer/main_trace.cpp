
#include "main_trace.hpp"
#include <vector>
#include <queue>
#include <ctime>
#include <thread>

#include "shapes.hpp"

Camera cam;
std::vector<Shape*> world;

void draw_pixels(int32_t* pixels, int w, int h,
                size_t start_x, size_t start_y, 
                size_t end_x, size_t end_y)
{
    for (size_t y = start_y; y < end_y; y++) {
        for (size_t x = start_x; x < end_x; x++) {
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

void trace(int32_t* pixels, int w, int h)
{
    cam = { {0, 0, 1}, {1, 1, 0}, 90.0, w, h };
    
    world.push_back(new Sphere{ {1, 1, -5000}, 5000, { 12, 200, 23 } });
    world.push_back(new Sphere{ {3, 3, 1}, 1 });

    std::thread draw_1(draw_pixels, pixels, w, h, 0, 0, w / 2, h / 2);
    std::thread draw_2(draw_pixels, pixels, w, h, w / 2, 0, w, h / 2);
    std::thread draw_3(draw_pixels, pixels, w, h, 0, h / 2, w / 2, h);
    std::thread draw_4(draw_pixels, pixels, w, h, w / 2, h / 2, w, h);

    draw_1.join();
    draw_2.join();
    draw_3.join();
    draw_4.join();
}
