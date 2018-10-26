
#include "main_trace.hpp"
#include <vector>
#include <queue>
#include <ctime>
#include <thread>

#include "shapes.hpp"

Camera cam;
std::vector<Shape*> world;

#define AA 5

uint32_t shoot_ray(const Ray& camera_ray, int depth) 
{
    uint32_t final_color = 0;

    double best_dist = -1;
    for (auto& x : world) {
        Vector intersec_point = x->ray_intersect(camera_ray);

        double current_dist = vec_distance(camera_ray.origin, intersec_point);
        if (current_dist > 0) {
            if (current_dist < best_dist || best_dist == -1) {
                final_color = x->color_at_vec(intersec_point);
                best_dist = current_dist;
            }
        }
    }

    return final_color;
}

void draw_pixels(uint32_t* pixels, int w, int h,
                size_t start_x, size_t start_y, 
                size_t end_x, size_t end_y)
{
    for (size_t y = start_y; y < end_y; y++) {
        for (size_t x = start_x; x < end_x; x++) {
            uint32_t& current_pixel = pixels[y*w + x];

            Ray camera_ray;
            Color final_color = { 0, 0, 0 };

            for (size_t i = 0; i < AA; i++) {
                camera_ray = cam.get_ray_on_pixel_rand(x, y);

                final_color += shoot_ray(camera_ray, 0);
            }

            current_pixel = final_color / (double)AA;
        }
    }
}

void trace(uint32_t* pixels, int w, int h)
{
    cam = { {0, 0, 1}, {1, 1, 0}, 90.0, w, h };
    
    world.push_back(new Sphere{ {10000, 10000, 50}, 20000, { 12, 32, 200 } });
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

    world.clear();
}
