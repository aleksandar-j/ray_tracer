#pragma once

class Vector;
class Ray;
class Shape;

class Intersect {

public:
    Intersect() : 
        point({}), ray_to_point_dist(0.0), shape_hit(nullptr), ray_shot({})
    {
    }
    Intersect(const Vector& point) :
        point(point), ray_to_point_dist(0.0), shape_hit(nullptr), ray_shot({})
    {
    }

    Vector point;

    Ray ray_shot;
    double ray_to_point_dist;

    const Shape* shape_hit;

};