#pragma once

#include "objects_list.hpp"

Color color_at_ray_intersect(const ObjectList& world, const Ray& ray)
{
    Intersect intersect = object_ray_intersect(world, ray);

    if (intersect.shape_hit != nullptr) {
        return color_at_point(world, intersect);
    } else {
        return BLACK;
    }
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

Color color_at_point(const ObjectList& world, const Intersect& intersect)
{
    Color object_color;

    // Get object's color at the point
    object_color = intersect.shape_hit->texture_at_point(intersect.point);
    
    // Get any reflections and edit our color
    Color reflection = reflect_light(world, intersect);

    // Lower the final color depending on the light level
    object_color *= light_level_at_point(world, intersect);

    return object_color;
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

Color reflect_light(const ObjectList& world, const Intersect& intersect) 
{
    Color result;

    if (intersect.shape_hit->material.albedo < 1.0) {
        // Shoot diffuse rays

        Ray normal = intersect.shape_hit->get_normal_ray_at_vec(intersect.point);
        normal.direction *= 2;
        normal.direction += rand_unit_vector();
        normal.direction.make_unit_vector();

        Intersect intersect_new = object_ray_intersect(world, normal);

        if (intersect_new.shape_hit != nullptr) {
            result = color_at_point(world, intersect_new);
            result *= 1.0 - intersect.shape_hit->material.albedo;
        } else {
            result = WHITE;
        }

    }

    return result;
}
