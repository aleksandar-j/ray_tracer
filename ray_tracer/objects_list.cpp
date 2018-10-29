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
    object_color = reflect_light(world, intersect, object_color);

    /*object_color.red = ((double)object_color.red / 255.0) * reflection.red;
    object_color.green = ((double)object_color.green / 255.0) * reflection.green;
    object_color.blue = ((double)object_color.blue / 255.0) * reflection.blue;*/

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

Color reflect_light(const ObjectList& world, const Intersect& intersect, const Color& object_color_in) 
{
    if ((intersect.shape_hit->material.diffuse + intersect.shape_hit->material.specular) > 1.0) {
        // More light out than in
        // TODO: raise error
    }

    Color diffuse_result;
    if (intersect.shape_hit->material.diffuse > 0.0) {
        // Shoot diffuse rays

        Ray normal = intersect.shape_hit->get_normal_ray_at_vec(intersect.point);
        normal.direction += rand_unit_vector();
        normal.direction.make_unit_vector();

        Intersect intersect_new = object_ray_intersect(world, normal);

        if (intersect_new.shape_hit != nullptr) {
            diffuse_result = color_at_point(world, intersect_new)*0.6 + object_color_in*0.4;
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
    
        Intersect intersect_new = object_ray_intersect(world, normal);

        if (intersect_new.shape_hit != nullptr) {
            specular_result = color_at_point(world, intersect_new);
        } else {
            specular_result = BLACK;
        }

        specular_result *= intersect.shape_hit->material.specular;

    }

    return diffuse_result + specular_result;
}
