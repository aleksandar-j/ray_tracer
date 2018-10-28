
#include "main_trace.hpp"
#include <vector>
#include <ctime>
#include <thread>

#include "camera.hpp"
#include "objects_list.hpp"

Camera cam;
ObjectList shapes;

#define AA 2

void draw_pixels(uint32_t* pixels, int w, int h,
                size_t start_x, size_t start_y, 
                size_t end_x, size_t end_y)
{
    for (size_t y = start_y; y < end_y; y++) {
        for (size_t x = start_x; x < end_x; x++) {
            Ray camera_ray;
            Color final_color = { 0, 0, 0 };

            bool run_aa = false;
            Color prev_color;
            for (size_t i = 0; i < AA; i++) {
                camera_ray = cam.get_ray_on_pixel(x*AA + i, y*AA + i);

                Intersect intersect = object_ray_intersect(shapes, camera_ray);
                Color new_color = color_at_point(shapes, intersect);

                if (i > 0) {
                    if (new_color != prev_color) {
                        run_aa = true;
                    }
                }

                prev_color = new_color;
                final_color += new_color;
            }

            if (run_aa) {
                for (size_t y_new = 0; y_new < AA; y_new++) {
                    for (size_t x_new = 0; x_new < AA; x_new++) {
                        if (x_new == y_new) {
                            // We already did this while testing whether we should do AA
                            continue;
                        }

                        camera_ray = cam.get_ray_on_pixel(x*AA + x_new, y*AA + y_new);

                        Intersect intersect = object_ray_intersect(shapes, camera_ray);
                        final_color += color_at_point(shapes, intersect);
                    }
                }
            }

            if (run_aa) {
                pixels[y*w + x] = final_color / ((double)AA*(double)AA);
            } else {
                pixels[y*w + x] = final_color / ((double)AA);
            }
        }
    }
}

void trace(uint32_t* pixels, int w, int h)
{
    cam = { {0, 0, 1}, {1, 1, 0}, 90.0, w * AA, h * AA };

    // Objects
    shapes.object_list.push_back(new Sphere{ {10000, 10000, 50}, 20000, { 135, 160, 255 } });
    shapes.object_list.push_back(new Sphere{ {1, 1, -5000}, 5000, { 12, 200, 23 } });

    shapes.object_list.push_back(new Sphere{ {3, 3, 1}, 1, {23, 48, 69} });
    shapes.object_list.push_back(new Sphere{ {3.2, 1.6, 0.6}, 0.05, {23, 48, 69} });
    shapes.object_list.push_back(new Sphere{ {4, 2, 2.5}, 0.3 });
    shapes.object_list.push_back(new Sphere{ {10, 2, 1.5}, 3 });
    shapes.object_list.push_back(new Sphere{ {2, 4, 2}, 0.5, {150, 23, 0} });
    shapes.object_list.push_back(new Sphere{ {0.5, 1.1, 0.7}, 0.3 });

    // Lights
    shapes.light_list.push_back(new AmbientLight{ 0.1 });
    shapes.light_list.push_back(new PointLight{ {3, 3, 5}, 1.0, 25.0 });
    shapes.light_list.push_back(new PointLight{ {5, 3, 2}, 1.0, 10.0 });
    shapes.light_list.push_back(new PointLight{ {2, 2, 0.7}, 0.2, 5.0 });
    
    // Worker treads
    std::thread draw_1(draw_pixels, pixels, w, h, 0, 0, w / 2, h / 2);
    std::thread draw_2(draw_pixels, pixels, w, h, w / 2, 0, w, h / 2);
    std::thread draw_3(draw_pixels, pixels, w, h, 0, h / 2, w / 2, h);
    std::thread draw_4(draw_pixels, pixels, w, h, w / 2, h / 2, w, h);

    draw_1.join();
    draw_2.join();
    draw_3.join();
    draw_4.join();
    
    // In case we call this trace function multiple times
    shapes.object_list.clear();
}
