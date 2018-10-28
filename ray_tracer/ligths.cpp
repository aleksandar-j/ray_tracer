
#include "ligths.hpp"

double PointLight::light_level_at_point(const std::vector<Shape*>& objects, const Intersect& intersect) const
{
    double result = 1.0;

    double lightpoint_dist = vec_distance(this->center, intersect.point);
    for (auto& object : objects) {
        Ray lightobject_ray{ {this->center}, {intersect.point - this->center} };
        Intersect intersect_data = object->ray_intersect(lightobject_ray);
        
        if (intersect_data.shape_hit == NULL) {
            // Nothing is hit, continue
            continue;
        }
        
        if (intersect_data.ray_to_point_dist < lightpoint_dist) {
            // We hit something that is closer than our point

            // We check whether the thing we hit is actually our point
            if (abs(lightpoint_dist - intersect_data.ray_to_point_dist) > 0.0001) {
                // Blocks light, we hit something before the point
                result = 0.0;
                break;
            } else {
                // This object doesn't block light
            }
        }
    }

    if (result != 0.0) {
        // We do hit the point

        Ray objectnormal_ray = intersect.shape_hit->get_normal_ray_at_vec(intersect.point);
        Vector objectlight_direction = { this->center - intersect.point };

        double angle = vec_anglebetween_rad(objectnormal_ray.direction, objectlight_direction);

        result *= abs(cos(angle));
    }

    return result;
}

double AmbientLight::light_level_at_point(const std::vector<Shape*>& objects, const Intersect& intersect) const
{
    return this->intensity;
}
