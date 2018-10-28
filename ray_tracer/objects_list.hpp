#pragma once

#include "vector.hpp"

#include "intersect.hpp"
#include "shapes.hpp"
#include "ligths.hpp"

class ObjectList {

public:
    ObjectList()
    {
    }
    ObjectList(std::vector<Shape*>& object_list, std::vector<Light*> light_list) :
        object_list(object_list), light_list(light_list)
    {
    }

    std::vector<Shape*> object_list;
    std::vector<Light*> light_list;

};

Intersect object_ray_intersect(const ObjectList& world, const Ray& ray);
Color color_at_point(const ObjectList& world, const Vector& point, const Shape& object);

double light_level_at_point(const ObjectList& world, const Vector& point);