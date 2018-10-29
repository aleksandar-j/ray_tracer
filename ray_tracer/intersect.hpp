#pragma once

class Vector;
class Ray;
class Shape;

class Intersect {

public:
    Intersect() : 
        point(), ray_to_point_dist(0.0), shape_hit(nullptr)
    {
    }

    Vector point;
    double ray_to_point_dist;

    Ray ray_shot;

    const Shape* shape_hit;

};