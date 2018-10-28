#pragma once

class Shape;

struct Intersect {

    Vector point;
    double ray_to_point_dist;

    const Shape* shape_hit;

};