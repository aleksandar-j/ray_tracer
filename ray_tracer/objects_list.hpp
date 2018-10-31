#pragma once

#include "shapes.hpp"
#include "ligths.hpp"

struct ObjectList {

    std::vector<Shape*> object_list;
    std::vector<Light*> light_list;

};

// Increase depth when you shoot new ray

Color color_at_ray_intersect(const ObjectList& world, const Ray& ray, int depth);
Color color_at_point(const ObjectList& world, const Intersect& intersect, int depth);

Color reflect_light(const ObjectList& world, const Intersect& intersect, const Color& object_color_in, int depth);

Intersect object_ray_intersect(const ObjectList& world, const Ray& ray);
double light_level_at_point(const ObjectList& world, const Intersect& intersect);