#pragma once

#include "vector.hpp"

#include "intersect.hpp"
#include "shapes.hpp"
#include "ligths.hpp"

struct ObjectList {

    std::vector<Shape*> object_list;
    std::vector<Light*> light_list;

};

Intersect object_ray_intersect(const ObjectList& world, const Ray& ray);
Color color_at_point(const ObjectList& world, const Intersect& intersect);

double light_level_at_point(const ObjectList& world, const Intersect& intersect);