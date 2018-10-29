#pragma once

#include "objects_list.hpp"

#define MAX_STACK_DEPTH 10

Color color_at_ray_intersect(const ObjectList& world, const Ray& ray, int depth)
{
    if (depth > MAX_STACK_DEPTH) {
        return BLACK;
    }

    Intersect intersect = object_ray_intersect(world, ray, depth);

    if (intersect.shape_hit != nullptr) {
        return color_at_point(world, intersect, depth);
    } else {
        return BLACK;
    }
}

Color color_at_point(const ObjectList& world, const Intersect& intersect, int depth)
{
    if (depth > MAX_STACK_DEPTH) {
        return BLACK;
    }

    Color object_color;

    // Get object's color at the point
    object_color = intersect.shape_hit->texture_at_point(intersect.point);

    // Lower the final color depending on the light level
    object_color *= light_level_at_point(world, intersect);

    // Get any reflections and edit our color
    object_color = reflect_light(world, intersect, object_color, depth);

    return object_color;
}

Intersect object_ray_intersect(const ObjectList& world, const Ray& ray, int depth)
{
    if (depth > MAX_STACK_DEPTH) {
        return {};
    }

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

double light_level_at_point(const ObjectList& world, const Intersect& intersect)
{
    double result = 0.0;
    
    for (auto& light : world.light_list) {
        double light_level = light->light_level_at_point(world.object_list, intersect);
        result += (1.0 - result) * light_level;
    }

    return result;
}

Color reflect_light(const ObjectList& world, const Intersect& intersect, const Color& object_color_in, int depth)
{
    if ((intersect.shape_hit->material.diffuse + intersect.shape_hit->material.specular) > 1.0) {
        // More light out than in
        // TODO: raise error
    }
    if (depth > MAX_STACK_DEPTH) {
        return object_color_in;
    }

    Color diffuse_result;
    if (intersect.shape_hit->material.diffuse > 0.0) {
        // Shoot diffuse rays

        Ray normal = intersect.shape_hit->get_normal_ray_at_vec(intersect.point);
        normal.direction += rand_unit_vector();
        normal.direction.make_unit_vector();

        Intersect intersect_new = object_ray_intersect(world, normal, depth + 1);

        if (intersect_new.shape_hit != nullptr) {
            // Objects that are closer will have a greater impact on our color

            constexpr double diffuse_length_lim = 0.01;
            if (intersect_new.ray_to_point_dist < diffuse_length_lim) {
                Color color_new = color_at_point(world, intersect_new, depth + 1);

                double diffuse_intensity = 1.0 - (intersect_new.ray_to_point_dist / diffuse_length_lim);
                diffuse_result = color_new*diffuse_intensity + object_color_in*(1.0 - diffuse_intensity);
            } else {
                diffuse_result = object_color_in;
            }
        } else {
            diffuse_result = object_color_in;
        }

        diffuse_result *= intersect.shape_hit->material.diffuse;

    }

    Color specular_result;
    if (intersect.shape_hit->material.specular > 0.0) {
        // Shoot specular rays

        Ray normal = intersect.shape_hit->get_normal_ray_at_vec(intersect.point);
        Vector reflected_vec = intersect.ray_shot.direction + normal.direction*2;

        Ray reflection = { normal.origin, reflected_vec };
    
        Intersect intersect_new = object_ray_intersect(world, normal, depth + 1);

        if (intersect_new.shape_hit != nullptr) {
            specular_result = color_at_point(world, intersect_new, depth + 1);
        } else {
            specular_result = BLACK;
        }

        specular_result *= intersect.shape_hit->material.specular;

    }

    return diffuse_result + specular_result;
}
