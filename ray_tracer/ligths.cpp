
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

        
    }

    return result;
}

double AmbientLight::light_level_at_point(const std::vector<Shape*>& objects, const Intersect& intersect) const
{
    return this->intensity;
}
