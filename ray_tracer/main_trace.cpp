
#include "main_trace.hpp"
#include <vector>
#include <ctime>
#include <thread>

#include "camera.hpp"
#include "objects_list.hpp"

Camera cam;
ObjectList shapes;

#define AA 5

#define AA_OPTIMIZE true
#define AA_OPTIMIZE_DIFFACCEPTED 5.0

void draw_pixels(uint32_t* pixels, int w, int h,
                size_t start_x, size_t start_y, 
                size_t end_x, size_t end_y)
{
    srand(time(0));

    for (size_t y = start_y; y < end_y; y++) {
        for (size_t x = start_x; x < end_x; x++) {
            Ray camera_ray;
            Color final_color;

            camera_ray = cam.get_ray_on_pixel(x*AA, y*AA);
            Color first_pixel = color_at_ray_intersect(shapes, camera_ray, 0);

            final_color = first_pixel;

            if (AA > 1) {
                bool run_aa = true;

                if (AA_OPTIMIZE && AA > 2) {
                    // Tracing four edge AA pixels, if all are similar, we don't do more
                    // Calculate color on current pixel lower left
                    camera_ray = cam.get_ray_on_pixel(x*AA, y*AA + (AA - 1));
                    final_color += color_at_ray_intersect(shapes, camera_ray, 0);

                    // Calculate color on current pixel upper right
                    camera_ray = cam.get_ray_on_pixel(x*AA + (AA - 1), y*AA);
                    final_color += color_at_ray_intersect(shapes, camera_ray, 0);

                    // Calculate color on current pixel lower right
                    camera_ray = cam.get_ray_on_pixel(x*AA + (AA - 1), y*AA + (AA - 1));
                    final_color += color_at_ray_intersect(shapes, camera_ray, 0);

                    // Get average final color
                    final_color /= 4.0;

                    if (color_average_diff(final_color, first_pixel) < AA_OPTIMIZE_DIFFACCEPTED) {
                        run_aa = false;
                    }
                }

                // If there are some different pixels, we run the full aa routines
                if (run_aa) {
                    final_color = {};

                    for (size_t y_new = 0; y_new < AA; y_new++) {
                        for (size_t x_new = 0; x_new < AA; x_new++) {
                            // Calculate color on current pixel
                            camera_ray = cam.get_ray_on_pixel(x*AA + x_new, y*AA + y_new);
                            final_color += color_at_ray_intersect(shapes, camera_ray, 0);
                        }
                    }

                    final_color /= ((double)AA*(double)AA);
                }
            }

            pixels[y*w + x] = final_color;
        }
    }
}

void trace(uint32_t* pixels, int w, int h)
{
    cam = { {0, 0, 1}, {1, 1, 0}, 90.0, w * AA, h * AA };

    // Objects
    shapes.object_list.push_back(new Sphere{ {0, 0, 0}, 50, TEAL, {0.5, 0.5} });
    shapes.object_list.push_back(new Sphere{ {1, 1, -5000}, 5000, WHITE, {1.0, 0.0} });

    shapes.object_list.push_back(new Sphere{ {3, 3, 1}, 1, NAVY, { 0.1, 0.9 } });
    shapes.object_list[2]->material.specular_fuzz = 0.005;
    shapes.object_list.push_back(new Sphere{ {2.5, 2.5, 2.5}, 0.5, MAROON });
    shapes.object_list.push_back(new Sphere{ {3.2, 1.6, 0.6}, 0.05, GREEN });
    shapes.object_list.push_back(new Sphere{ {4, 2, 2.5}, 0.3, NAVY });
    shapes.object_list.push_back(new Sphere{ {10, 2, 1.5}, 3, PURPLE, { 0.7, 0.3 } });
    shapes.object_list[6]->material.specular_fuzz = 0.1;
    shapes.object_list.push_back(new Sphere{ {2, 4, 2}, 0.5, AQUA });
    shapes.object_list.push_back(new Sphere{ {0.5, 1.1, 0.7}, 0.3, YELLOW });

    // Lights
    shapes.light_list.push_back(new AmbientLight{ 0.1 });
    shapes.light_list.push_back(new PointLight{ {5, 3, 2}, 1.0, 25.0 });
    shapes.light_list.push_back(new PointLight{ {2, 2, 0.7}, 0.2, 10.0 });

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
