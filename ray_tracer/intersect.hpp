#pragma once

class Shape;

class Intersect {

public:
    Intersect() : 
        point(), ray_to_point_dist(0.0), shape_hit(nullptr)
    {
    }

    Vector point;
    double ray_to_point_dist;

    const Shape* shape_hit;

};