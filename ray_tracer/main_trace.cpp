
#include "main_trace.hpp"
#include <vector>
#include <queue>
#include <ctime>
#include <thread>

#include "shapes.hpp"

Camera cam;
std::vector<Shape*> world;

#define AA 10
#define NUM_THREADS 4

uint32_t shoot_ray(const Ray& ray, int depth) 
{
    uint32_t final_color = 0;
    Shape* final_shape = NULL;
    Vector final_intersect;

    double best_dist = -1;
    for (auto& x : world) {
        Vector intersec_point = x->ray_intersect(ray);

        double current_dist = vec_distance(ray.origin, intersec_point);
        if (current_dist > 0) {
            if (current_dist < best_dist || best_dist == -1) {
                best_dist = current_dist;

                final_color = x->color_at_vec(intersec_point);
                final_shape = x;
                final_intersect = intersec_point;
            }
        }
    }

    if (depth > 5) {
        return final_color;
    }

    if (final_shape) {
        Ray normal = final_shape->get_normal_ray_at_vec(final_intersect);
        normal.direction.rotate_x_deg((double)(rand() % 90 - 45));
        normal.direction.rotate_y_deg((double)(rand() % 90 - 45));
        normal.direction.rotate_z_deg((double)(rand() % 90 - 45));
        /*final_color = Color{ (int)(abs(normal.direction.x)*254.0), 
                             (int)(abs(normal.direction.y)*254.0), 
                             (int)(abs(normal.direction.z)*254.0) };*/
        uint32_t normal_color = shoot_ray(normal, depth + 1);
        final_color -= 0.2*Color{ (int)normal_color };
    }

    return final_color;
}

void draw_pixels(uint32_t* pixels, int w, int h,
                size_t start_x, size_t start_y, 
                size_t end_x, size_t end_y)
{
    for (size_t y = start_y; y < end_y; y++) {
        for (size_t x = start_x; x < end_x; x++) {
            Ray camera_ray;
            Color final_color = { 0, 0, 0 };

            for (size_t i = 0; i < AA; i++) {
                camera_ray = cam.get_ray_on_pixel_rand(x, y);

                final_color += shoot_ray(camera_ray, 0);
            }

            pixels[y*w + x] = final_color / (double)AA;
        }
    }
}

void trace(uint32_t* pixels, int w, int h)
{
    cam = { {0, 0, 1}, {1, 1, 0}, 90.0, w, h };
    
    world.push_back(new Sphere{ {10000, 10000, 50}, 20000, { 12, 32, 200 } });
    world.push_back(new Sphere{ {1, 1, -5000}, 5000, { 12, 200, 23 } });
    world.push_back(new Sphere{ {3, 3, 1}, 1 });
    world.push_back(new Sphere{ {4, 2, 0.7}, 0.9 });

    std::vector<std::thread*> threads;

    for (size_t i = 0; i < NUM_THREADS; i++) {
        std::thread* draw = new std::thread(draw_pixels, pixels, w, h, 0, (h / NUM_THREADS) * i, w, (h / NUM_THREADS) * (i + 1));
        threads.push_back(draw);
    }

    for (size_t i = 0; i < NUM_THREADS; i++) {
        threads[i]->join();
    }
    
    // TODO: Not sure if this deletes pointers
    threads.clear();
    world.clear();
}
