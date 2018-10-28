
#include "shapes.hpp"

Intersect ShapeList::ray_intersect(const Ray& ray) const
{
    Intersect final_intersect;

    double best_dist = -1;
    for (auto& x : this->list) {
        Intersect intersect_data = x->ray_intersect(ray);
        double dist_to_intersect = intersect_data.ray_to_point_dist;

        if (dist_to_intersect > 0) {
            if (dist_to_intersect < best_dist || best_dist == -1) {
                best_dist = dist_to_intersect;
                final_intersect = intersect_data;
            }
        }
    }

    return final_intersect;
}

Color ShapeList::color_at_vec(const Vector & point) const
{
    return Color();
}

Ray ShapeList::get_normal_ray_at_vec(const Vector & point) const
{
    return Ray();
}

Intersect Cube::ray_intersect(const Ray & ray) const
{
    return Intersect();
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

Color Sphere::color_at_vec(const Vector& point) const
{
    // TODO: texture mapping
    return this->color;
}

Ray Sphere::get_normal_ray_at_vec(const Vector& point) const
{
    return { point, { point - this->center } };
}
