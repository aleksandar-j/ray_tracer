
#include "shapes.hpp"

Vector Cube::ray_intersect(const Ray & ray) const
{
    return Vector();
}

Vector Sphere::ray_intersect(const Ray& ray) const
{
    Vector cam_to_center{ this->center - ray.origin };
    double dist_cam_to_center = cam_to_center.magnitude();
    double dist_cam_from_center_normal = vec_dot_product(cam_to_center, ray.direction);

    double dist_ray_from_center = 
        sqrt(dist_cam_to_center*dist_cam_to_center - dist_cam_from_center_normal*dist_cam_from_center_normal);
    if (dist_ray_from_center > this->radius) {
        return ray.origin;
    }

    double dist_from_intersections = 2 * sqrt(this->radius*this->radius - dist_ray_from_center*dist_ray_from_center);

    double dist_cam_to_intersec_1 = dist_cam_from_center_normal - dist_from_intersections / 2;
    double dist_cam_to_intersec_2 = dist_cam_from_center_normal + dist_from_intersections / 2;

    if (dist_cam_to_intersec_1 > 0 || dist_cam_to_intersec_2 > 0) {
        if (dist_cam_to_intersec_1 > 0 && dist_cam_to_intersec_1 < dist_cam_to_intersec_2) {
            return ray.origin + (ray.direction * dist_cam_to_intersec_1);
        } else {
            return ray.origin + (ray.direction * dist_cam_to_intersec_2);
        }
    } else {
        return ray.origin;
    }
}

Color Sphere::color_at_vec(const Vector& point) const
{
    // TODO: texture mapping
    return this->color;
}

Ray Sphere::get_normal_ray_at_vec(const Vector& point) const
{
    return { point, { point - this->center } };
}
