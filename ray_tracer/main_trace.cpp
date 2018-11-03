
#include "main_trace.hpp"
#include <vector>
#include <ctime>
#include <thread>
#include <mutex>

#include "camera.hpp"
#include "objects_list.hpp"

#include "render_settings.hpp"

Camera cam;
ObjectList world;

void draw_pixels(uint32_t* pixels, int w, int h,
                    size_t start_y, size_t end_y, 
                    int screen_part)
{
    srand((unsigned int)time(0));

    for (size_t y = start_y; y < end_y; y++) {
        for (size_t x = 0; x < w; x++) {
            Ray camera_ray = cam.get_ray_on_pixel(x*AA, y*AA);
            Color first_pixel = color_at_ray_intersect(world, camera_ray, 0);

            Color final_color = first_pixel;

            if (AA > 1) {
                bool run_aa = true;

                if (AA_OPTIMIZE && AA > 2) {
                    // Tracing four edge AA pixels, if all are similar, we don't do more

                    // Calculate color on current pixel lower left
                    camera_ray = cam.get_ray_on_pixel(x*AA, y*AA + (AA - 1));
                    final_color += color_at_ray_intersect(world, camera_ray, 0);

                    // Calculate color on current pixel upper right
                    camera_ray = cam.get_ray_on_pixel(x*AA + (AA - 1), y*AA);
                    final_color += color_at_ray_intersect(world, camera_ray, 0);

                    // Calculate color on current pixel lower right
                    camera_ray = cam.get_ray_on_pixel(x*AA + (AA - 1), y*AA + (AA - 1));
                    final_color += color_at_ray_intersect(world, camera_ray, 0);

                    // Get average final color
                    final_color /= 4.0;

                    if (run_aa) {
                        if (color_greatest_diff(final_color, first_pixel) < AA_OPTIMIZE_MAXDIFFACCEPTED) {
                            run_aa = false;
                        }
                    }
                    if (run_aa) {
                        if (color_average_diff(final_color, first_pixel) < AA_OPTIMIZE_AVGDIFFACCEPTED) {
                            run_aa = false;
                        }
                    }
                }

                // If there are some different pixels, we run the full aa routines
                if (run_aa) {
                    final_color = {};

                    size_t x_new = 0, y_new = 0;
                    for (y_new = 0; y_new < AA; y_new++) {
                        camera_ray = cam.get_ray_on_pixel(x*AA + x_new, y*AA + y_new);

                        for (x_new = 0; x_new < AA; x_new++) {
                            cam.get_ray_on_pixel_next_horz(camera_ray);

                            final_color += color_at_ray_intersect(world, camera_ray, 0);
                        }
                    }

                    final_color /= ((double)AA*(double)AA);
                }
            }

            pixels[y*w + x] = final_color;
        }
    }
}

std::mutex screen_drawing;
std::vector<bool> screens_drawn(NUM_SCREENS, false);

int get_free_screen_part() 
{
    int result = -1;

    screen_drawing.lock();
    for (size_t i = 0; i < NUM_SCREENS; i++) {
        if (screens_drawn[i] == false) {
            screens_drawn[i] = true;
            result = i;
            break;
        }
    }
    screen_drawing.unlock();

    return result;
}

void thread_manager(uint32_t* pixels, int w, int h) 
{
    while (true) {
        int i = get_free_screen_part();

        if (i == -1) {
            break;
        }

        int start_y = i * (h / NUM_SCREENS);
        int end_y = start_y + (h / NUM_SCREENS);

        std::thread down{ draw_pixels, pixels, w, h, start_y, end_y, i };
        
        down.join();
    }
}

void trace(uint32_t* pixels, int w, int h)
{
    // Load settings from file
    load_settings();

    cam = { {0, 0, 1}, {1, 1, 0}, 90.0, w * AA, h * AA };

    // Objects
    //world.object_list.push_back(new Sphere{ {0, 0, 0}, 10, TEAL });
    world.object_list.push_back(new Sphere{ {0, 0, -50000}, 50000, WHITE, {1.0, 0.0} });

    world.object_list.push_back(new Sphere{ {3, 3, 1}, 1, WHITE, { 1.0, 0.0 } });
    world.object_list[1]->material.specular_fuzz = 0.05;
    world.object_list.push_back(new Sphere{ {2.5, 2.5, 2.5}, 0.5, MAROON });
    world.object_list.push_back(new Sphere{ {3.2, 1.6, 0.6}, 0.05, GREEN });
    world.object_list.push_back(new Sphere{ {4, 2, 2.5}, 0.3, NAVY });
    world.object_list.push_back(new Sphere{ {10, 2, 1.5}, 3, PURPLE, { 0.5, 0.5 } });
    world.object_list[5]->material.specular_fuzz = 0.1;
    world.object_list.push_back(new Sphere{ {2, 4, 2}, 0.5, AQUA });
    world.object_list.push_back(new Sphere{ {0.5, 1.1, 0.7}, 0.3, YELLOW });

    // Lights
    world.light_list.push_back(new PointLight{ {5, 3, 2}, 0.5 });
    world.light_list.push_back(new PointLight{ {2, 2, 0.7}, 0.5 });

    // Atmospheres
    world.atmospheres_list.push_back(new Atmosphere{ new Sphere{ {0,0,0}, 50.0 }, 100, 0.3 });

    // Worker treads
    std::vector<std::thread> threads;

    for (size_t i = 0; i < NUM_THREADS; i++) {
        threads.push_back(std::thread{ thread_manager, pixels, w, h });
    }

    for (auto& x : threads) {
        x.join();
    }
    
    // In case we call this trace function multiple times
    world.object_list.clear();
}
