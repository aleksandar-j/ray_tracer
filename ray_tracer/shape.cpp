
#include "shape.hpp"

Sphere::Sphere() 
{
}
Sphere::Sphere(const Vector& center, const double radius) 
    :
    center(center), radius(radius)
{
}
Sphere::Sphere(const Vector& center, const double radius, const Color& color) 
    :
    center(center), radius(radius), color(color)
{
}
Sphere::Sphere(const Vector& center, const double radius,
               const Color& color, const Material& material) 
    :
    center(center), radius(radius), color(color)
{
    this->material = material;
}

Intersect Sphere::ray_intersect(const Ray& ray) const
{
    Intersect result = {};

    Vector cam_to_center{ this->center - ray.origin };
    double dist_cam_to_center = cam_to_center.magnitude();
    double dist_cam_from_center_normal = vec_dot_product(cam_to_center, ray.direction);

    double dist_ray_from_center_sqrd = 
        dist_cam_to_center*dist_cam_to_center - dist_cam_from_center_normal*dist_cam_from_center_normal;
    if (dist_ray_from_center_sqrd > (this->radius*this->radius)) {
        return result;
    }

    *this;

    double dist_from_intersections = 2 * sqrt(this->radius*this->radius - dist_ray_from_center_sqrd);

    double dist_cam_to_intersec_1 = dist_cam_from_center_normal - dist_from_intersections / 2;
    double dist_cam_to_intersec_2 = dist_cam_from_center_normal + dist_from_intersections / 2;

    if (dist_cam_to_intersec_1 > 0 || dist_cam_to_intersec_2 > 0) {
        result.shape_hit = this;

        if (dist_cam_to_intersec_1 > 0 && dist_cam_to_intersec_1 < dist_cam_to_intersec_2) {
            result.point = ray.origin + (ray.direction * dist_cam_to_intersec_1);
            result.ray_to_point_dist = dist_cam_to_intersec_1;
        } else {
            result.point = ray.origin + (ray.direction * dist_cam_to_intersec_2);
            result.ray_to_point_dist = dist_cam_to_intersec_2;
        }

        return result;
    } else {
        return result;
    }
}

bool Sphere::point_in_object(const Vector& point) const
{
    return vec_distance(point, this->center) < this->radius;
}

Ray Sphere::normal_ray_at_point(const Vector& point) const
{
    return { point, { point - this->center } };
}

Color Sphere::color_at_point(const Vector& point) const
{
    return this->color;
}
