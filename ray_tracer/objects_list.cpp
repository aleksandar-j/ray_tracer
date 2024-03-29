
#include "objects_list.hpp"

#include "render_settings.hpp"

#include <cmath>

Color color_at_ray_intersect(const ObjectList& world, const Ray& ray, int depth)
{
    if (depth > MAX_STACK_DEPTH) {
        return GRAY;
    }

    Intersect intersect = object_ray_intersect(world, ray);

    if (intersect.shape_hit != nullptr) {
        return color_at_point(world, intersect, depth);
    } else {
        return BLACK;
    }
}

Color color_at_point(const ObjectList& world, const Intersect& intersect, int depth)
{
    if (depth > MAX_STACK_DEPTH) {
        return GRAY;
    }

    Color object_color;

    // Get object's color at the point
    object_color = intersect.shape_hit->color_at_point(intersect.point);

    // Get any reflections and edit our color
    if (RUN_REFLECTION) {
        object_color = reflect_light(world, intersect, object_color, depth);
    }

    // Adjust the final color depending on the light level
    if (RUN_LIGHT) {
        object_color = light_color_at_point(world, intersect, object_color, nullptr, depth);
    }

    return object_color;
}

Intersect object_ray_intersect(const ObjectList& world, const Ray& ray)
{
    Intersect final_intersect;
    final_intersect.ray_shot = ray;

    double best_dist = -1;
    for (auto& x : world.object_list) {
        Intersect intersect_data = x->ray_intersect(ray);
        double dist_to_intersect = intersect_data.ray_to_point_dist;

        if (dist_to_intersect > 0.00001) {
            if (dist_to_intersect < best_dist || best_dist == -1) {
                best_dist = dist_to_intersect;
                final_intersect = intersect_data;
            }
        }
    }

    return final_intersect;
}

Atmosphere vacuum = Atmosphere{ new Sphere{ {0, 0, 0}, MAX_DOUBLE }, MAX_DOUBLE, 0.0 };
Atmosphere atmosphere_at_point(const ObjectList& world, const Vector& point)
{
    Atmosphere* result = &vacuum;

    double greatest_density = -0.1;
    for (auto& x : world.atmospheres_list) {
        // We go through all our atmospheres

        if (x->density > greatest_density) {
            // Atmosphere with greatest density wins

            if (x->atmosphere_shape->point_in_object(point)) {
                // Our atmosphere surrounds the point

                result = x;
                greatest_density = x->density;
            }
        }
    }

    return *result;
}

Color reflect_light(const ObjectList& world, const Intersect& intersect,
    const Color& object_color_in,
    int depth)
{
    if ((intersect.shape_hit->material.diffuse + intersect.shape_hit->material.specular) != 1.0) {
        // More light out/in than in/out (in is 1.0 - 100%, out must also be 1.0 - 100%)
        throw "reflect_light got an object with more/less than 1.0 light amount";
    }
    if (depth > MAX_STACK_DEPTH) {
        return object_color_in;
    }

    Color diffuse_result = object_color_in;
    if (RUN_REFLECTION_DIFFUSE && intersect.shape_hit->material.diffuse > 0.0) {
        // Shoot diffuse rays

        Ray rand_reflected_ray = { intersect.point, intersect.point_hit_normal + rand_unit_vector() };
        Intersect intersect_new = object_ray_intersect(world, rand_reflected_ray);

        if (intersect_new.shape_hit) {
            double red_energy_left = object_color_in.red / 255.0;
            double green_energy_left = object_color_in.green / 255.0;
            double blue_energy_left = object_color_in.blue / 255.0;

            diffuse_result = color_at_point(world, intersect_new, depth + STACK_DEPTH_DIFFUSE_ADD) * Color{red_energy_left, green_energy_left, blue_energy_left};
        }
    }
    diffuse_result *= intersect.shape_hit->material.diffuse;

    Color specular_result = BLACK;
    if (RUN_REFLECTION_SPECULAR && intersect.shape_hit->material.specular > 0.0) {
        // Shoot specular rays

        Vector reflected_vec = intersect.ray_shot.direction + intersect.point_hit_normal * 2;

        Ray reflection = { intersect.point, reflected_vec };

        // Specular Fuzz implementation
        if (intersect.shape_hit->material.specular_fuzz > 0.0) {
            reflection.direction += rand_unit_vector() * intersect.shape_hit->material.specular_fuzz;
            reflection.direction.make_unit_vector();
        }

        Intersect intersect_new = object_ray_intersect(world, reflection);

        if (intersect_new.shape_hit != nullptr) {
            specular_result = color_at_point(world, intersect_new, depth + STACK_DEPTH_SPECULAR_ADD);
        } else {
            specular_result = BLACK;
        }
    }
    specular_result *= intersect.shape_hit->material.specular;

    return diffuse_result + specular_result;
}

Color light_color_at_point(const ObjectList& world, const Intersect& intersect,
                           const Color& object_color_in, double* light_intensity_at_point_out,
                           int depth)
{
    if (depth > MAX_STACK_DEPTH) {
        return 0;
    }

    Color final_light_color = {};
    double final_intensity = 0.0;

    for (auto& light : world.light_list) {
        // Get light level of each individual light at the point

        // This is how strong the light is at the point, from 0-1 doesn't take intensity into account
        double light_level = light->light_level_at_point(world, intersect);
        double light_intensity = light_level * light->intensity;

        // Blend the light color and our color, on first run fin_inten is 0 - all light color comes, later blends
        final_light_color = color_mix_weights(final_light_color, final_intensity, light->light_color, light_intensity);

        // Light intensity of 1.0 fills the whole remainder (1.0 - result), others fill only partially
        final_intensity += (1.0 - final_intensity) * light_intensity;
    }

    // Atmosphere refractions
    if (RUN_LIGHT_ATMOSPHERE) {
        // Calculating atmosphere-light interaction

        for (size_t i = 0; i < MAX_ATMOSPHERE_ITERATIONS; i++) {
            // Pick random points around our main one and see their light levels...

            Vector close_point;
            double close_point_distance;
            if (intersect.shape_hit && (rand() % 2)) {
                // We only try this once
                close_point = { intersect.point + (intersect.point_hit_normal + rand_unit_vector())*(i + 1) };
                close_point_distance = vec_distance(intersect.point, close_point);
            } else {
                close_point = { (intersect.point + rand_unit_vector()) * (i + 1) };
                close_point_distance = i + 1.0;
            }

            double close_point_light_intensity = 0.0;
            Color close_point_light_color = light_color_at_point(world, { close_point },
                                                        BLACK, &close_point_light_intensity,
                                                        depth + STACK_DEPTH_ATMOSPHERE_ADD);

            if (close_point_light_intensity == 0.0) {
                // The point is dark...
                continue;
            } else {
                // We managed to get some light, there is no need to check as many times...

                if (MAX_ATMOSPHERE_ITERATIONS > 2) {
                    // But we will still do it if iteration number is low...
                    i += 2;
                }
            }

            Atmosphere our_atmosphere = atmosphere_at_point(world, intersect.point);
            Atmosphere close_point_atmosphere = atmosphere_at_point(world, close_point);

            if (our_atmosphere.atmosphere_shape == close_point_atmosphere.atmosphere_shape) {
                // Same atmospheres, no light transition happens

                double distance_intensity_falloff = (our_atmosphere.light_dropoff_intensity - close_point_distance) /
                                                                our_atmosphere.light_dropoff_intensity;

                // We multiply by density because if in vacuum (0) - no refractions, but strong lights at distance
                //  if in very dense material (1) - very great refractions but light difficult to travel
                double refracted_light_intensity = close_point_light_intensity * distance_intensity_falloff *
                                                    our_atmosphere.light_refraction_amount;

                // Mix with our color
                final_light_color = color_mix_weights(final_light_color, final_intensity,
                                                close_point_light_color, refracted_light_intensity);

                // Increase intensity
                final_intensity += (1.0 - final_intensity) * refracted_light_intensity;
            } else {
                // TODO: Atmosphere transition, probably difficult to write through how many atmospheres we pass
            }
        }
    }

    // Give the calculated intensity back to the caller, if he gave a valid pointer
    if (light_intensity_at_point_out != nullptr) {
        *light_intensity_at_point_out = final_intensity;
    }

    // Mix the object color with the light color based on light intensity
    Color final_color = color_mix_weights(object_color_in, 1.0 - final_intensity, final_light_color, final_intensity);

    // 0.5 intensity is the default color so mult by 2, see light header
    final_color = color_safe_multiply(final_color, final_intensity*2);

    return final_color;
}
