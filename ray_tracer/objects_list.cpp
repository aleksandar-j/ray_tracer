#pragma once

#include "objects_list.hpp"

Intersect object_ray_intersect(const ObjectList& world, const Ray& ray)
{
    Intersect final_intersect;

    double best_dist = -1;
    for (auto& x : world.object_list) {
        Intersect intersect_data = x->ray_intersect(ray);
        double dist_to_intersect = intersect_data.ray_to_point_dist;

        if (dist_to_intersect > 0) {
            if (dist_to_intersect < best_dist || best_dist == -1) {
                best_dist = dist_to_intersect;
                final_intersect = intersect_data;
            }
        }
    }

    return final_intersect;
}

Color color_at_point(const ObjectList& world, const Vector& point, const Shape& object)
{
    Color object_color = object.color_at_point(point, object);
    object_color *= light_level_at_point(world, point);
    return object_color;
}

double light_level_at_point(const ObjectList& world, const Vector& point)
{
    double result = 0.0;

    // TODO: we only compute largest light level, not real one 
    //       (a .3 and a .5 light doesn't give .5 light)...
    for (auto& light : world.light_list) {
        double light_level = light->light_level_at_point(world.object_list, point);
        result = (light_level > result) ? light_level : result;
    }

    return result;
}