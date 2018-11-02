#pragma once

class Vector;
class Ray;
class Shape;

class Intersect {

public:
    Intersect()
    {
    }
    Intersect(const Vector& point)
        :
        point(point)
    {
    }

    // Point in 3D space that we are using
    Vector point = {};

    // If camera or some reflection shoot rays, they would be initialized here
    Ray ray_shot = {};
    double ray_to_point_dist = 0.0;

    // If the point lies on the shape, this is the pointer to that shape
    const Shape* shape_hit = nullptr;

};