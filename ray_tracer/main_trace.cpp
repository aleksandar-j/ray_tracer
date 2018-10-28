
#include "main_trace.hpp"
#include <vector>
#include <ctime>
#include <thread>

#include "shapes.hpp"
#include "camera.hpp"
#include "intersect.hpp"

Camera cam;
ShapeList shapes;

#define AA 20

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
                
                Intersect intersect = shapes.ray_intersect(camera_ray);
                Color color = intersect.shape_hit->color_at_vec(intersect.point);
                final_color += color;
            }

            pixels[y*w + x] = final_color / (double)AA;
        }
    }
}

void trace(uint32_t* pixels, int w, int h)
{
    cam = { {0, 0, 1}, {1, 1, 0}, 90.0, w, h };

    shapes.list.push_back(new Sphere{ {10000, 10000, 50}, 20000, { 135, 160, 255 } });
    shapes.list.push_back(new Sphere{ {1, 1, -5000}, 5000, { 12, 200, 23 } });

    shapes.list.push_back(new Sphere{ {3, 3, 1}, 1, {23, 48, 69} });
    shapes.list.push_back(new Sphere{ {4, 2, 2.5}, 0.3 });
    shapes.list.push_back(new Sphere{ {10, 2, 1.5}, 3 });
    shapes.list.push_back(new Sphere{ {2, 4, 2}, 0.5, {150, 23, 0} });
    shapes.list.push_back(new Sphere{ {0.5, 1.1, 0.7}, 0.3 });

    std::thread draw_1(draw_pixels, pixels, w, h, 0, 0, w / 2, h / 2);
    std::thread draw_2(draw_pixels, pixels, w, h, w / 2, 0, w, h / 2);
    std::thread draw_3(draw_pixels, pixels, w, h, 0, h / 2, w / 2, h);
    std::thread draw_4(draw_pixels, pixels, w, h, w / 2, h / 2, w, h);

    draw_1.join();
    draw_2.join();
    draw_3.join();
    draw_4.join();
    
    shapes.list.clear();
}
