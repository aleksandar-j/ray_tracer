#pragma once

#include <vector>

#include "shape.hpp"
#include "light.hpp"
#include "atmosphere.hpp"

// Rendering switches
#define RUN_REFLECTION (true)
#define RUN_REFLECTION_DIFFUSE (true)
#define RUN_REFLECTION_SPECULAR (true)
#define RUN_LIGHT (true)
#define RUN_LIGHT_ATMOSPHEREREF (true)

// Maximum depth baseline
#define MAX_STACK_DEPTH (100.0)

// What is the maximum times these could get called, given that they are only ones called
#define STACK_DEPTH_ATMOSPHERE (5.0)
#define STACK_DEPTH_DIFFUSE (3.0)
#define STACK_DEPTH_SPECULAR (3.0)

// How much do we increase depth for any operation
#define STACK_DEPTH_ATMOSPHERE_ADD (MAX_STACK_DEPTH / STACK_DEPTH_ATMOSPHERE)
#define STACK_DEPTH_DIFFUSE_ADD (MAX_STACK_DEPTH / STACK_DEPTH_DIFFUSE)
#define STACK_DEPTH_SPECULAR_ADD (MAX_STACK_DEPTH / STACK_DEPTH_SPECULAR)

// How many times do we run the atmosphere light check in the worst case, best case is half that
#define MAX_ATMOSPHERE_ITERATIONS 2

struct ObjectList {

    std::vector<Shape*> object_list;
    std::vector<Light*> light_list;
    std::vector<Atmosphere*> atmospheres_list;

};

// Increase depth when you shoot new ray
Color color_at_ray_intersect(const ObjectList& world, const Ray& ray, 
                             int depth);
Color color_at_point(const ObjectList& world, const Intersect& intersect, 
                     int depth);

Intersect object_ray_intersect(const ObjectList& world, const Ray& ray);
Atmosphere atmosphere_at_point(const ObjectList& world, const Vector& point);

Color reflect_light(const ObjectList& world, const Intersect& intersect, 
                    const Color& object_color_in, 
                    int depth);

Color light_color_at_point(const ObjectList& world, const Intersect& intersect, 
                           const Color& object_color_in, double* light_intensity_at_point_out, 
                           int depth);