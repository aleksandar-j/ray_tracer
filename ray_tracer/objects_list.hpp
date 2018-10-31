#pragma once

#include <vector>

#include "shape.hpp"
#include "light.hpp"
#include "atmosphere.hpp"

struct ObjectList {

    std::vector<Shape*> object_list;
    std::vector<Light*> light_list;
    std::vector<Atmosphere*> atmospheres_list;

};

// Increase depth when you shoot new ray
Color color_at_ray_intersect(const ObjectList& world, const Ray& ray, int depth);
Color color_at_point(const ObjectList& world, const Intersect& intersect, int depth);

Intersect object_ray_intersect(const ObjectList& world, const Ray& ray);
Atmosphere atmosphere_at_point(const ObjectList& world, const Vector& point);

Color reflect_light(const ObjectList& world, const Intersect& intersect, const Color& object_color_in, int depth);

double light_level_at_point(const ObjectList& world, const Intersect& intersect);