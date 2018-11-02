
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

    Vector ray_to_center{ this->center - ray.origin };

    // Distance from ray origin to the center of the sphere
    double dist_ray_to_center = ray_to_center.magnitude();
    // Distance from ray origin in direction of ray.direction to the point where normal cuts the center
    double dist_raydirection_from_center_normal = vec_dot_product(ray_to_center, ray.direction);

    // How far is the raydirection from the center
    double dist_raydirection_from_center_sqrd =
        dist_ray_to_center * dist_ray_to_center - dist_raydirection_from_center_normal * dist_raydirection_from_center_normal;

    if (dist_raydirection_from_center_sqrd > (this->radius*this->radius)) {
        // Our ray is farther from the center than sphere radius, no hit
        return result;
    }

    // We do hit the sphere, but where?

    double dist_from_intersections = 2 * sqrt(this->radius*this->radius - dist_raydirection_from_center_sqrd);

    double dist_cam_to_intersec_1 = dist_raydirection_from_center_normal - dist_from_intersections / 2;
    double dist_cam_to_intersec_2 = dist_raydirection_from_center_normal + dist_from_intersections / 2;

    if (dist_cam_to_intersec_1 > 0 && dist_cam_to_intersec_1 < dist_cam_to_intersec_2) {
        result.shape_hit = this;
        result.point = ray.origin + (ray.direction * dist_cam_to_intersec_1);
        result.ray_to_point_dist = dist_cam_to_intersec_1;
        result.point_hit_normal = get_unit_vector({ result.point - this->center });
    } else if (dist_cam_to_intersec_2 > 0) {
        result.shape_hit = this;
        result.point = ray.origin + (ray.direction * dist_cam_to_intersec_2);
        result.ray_to_point_dist = dist_cam_to_intersec_2;
        result.point_hit_normal = get_unit_vector({ result.point - this->center });
    }

    return result;
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
