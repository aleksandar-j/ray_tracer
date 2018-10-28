
#include "main_trace.hpp"
#include <vector>
#include <ctime>
#include <thread>

#include "shapes.hpp"
#include "camera.hpp"

Camera cam;
std::vector<Shape*> world;

#define AA 20

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
        Color new_col = final_color;
        double angle = vec_dot_product(Vector{ 0, 0, 0 } - normal.direction, cam.direction) / (normal.direction.magnitude() * cam.direction.magnitude());
        if (angle < 0.3) { angle = 0.3; }
        new_col = new_col * angle;
        //new_col = new_col * 1.5;
        final_color = new_col;
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
    
    world.push_back(new Sphere{ {10000, 10000, 50}, 20000, { 135, 160, 255 } });
    world.push_back(new Sphere{ {1, 1, -5000}, 5000, { 12, 200, 23 } });

    world.push_back(new Sphere{ {3, 3, 1}, 1, {23, 48, 69} });
    world.push_back(new Sphere{ {4, 2, 2.5}, 0.3 });
    world.push_back(new Sphere{ {10, 2, 1.5}, 3 });
    world.push_back(new Sphere{ {2, 4, 2}, 0.5, {150, 23, 0} });
    world.push_back(new Sphere{ {0.5, 1.1, 0.7}, 0.3 });

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
