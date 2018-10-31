
#include "ligth.hpp"

#include "objects_list.hpp"

double PointLight::light_level_at_point(const ObjectList& objects, const Intersect& intersect) const
{
    double result = 1.0;

    // Distance between light and point hit
    double lightpoint_dist = vec_distance(this->center, intersect.point);

    if (this->intensity_dropoff_linear < lightpoint_dist) {
        // Even if we can hit the point, light is too weak there
        return 0.0;
    }

    double light_at_distance = (this->intensity_dropoff_linear - lightpoint_dist) / this->intensity_dropoff_linear;

    // Angle between light and point hit normal
    Ray objectnormal_ray = intersect.shape_hit->get_normal_ray_at_vec(intersect.point);
    Vector objectlight_direction = { this->center - intersect.point };
    double angle = vec_anglebetween_rad(objectnormal_ray.direction, objectlight_direction);

    for (auto& object : objects.object_list) {
        // We check whether some other object blocks us from hitting the main one

        Ray lightobject_ray{ {this->center}, {intersect.point - this->center} };
        Intersect intersect_data = object->ray_intersect(lightobject_ray);
        
        if (intersect_data.shape_hit == nullptr) {
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

    if (result == 0.0) {
        // Light is blocked, but by how much?

        // TODO: Maybe sample close points? What is a close point?...
    } else {
        // We do hit the point

        // The greater the distance between the light and surface, the lower the light level
        result *= light_at_distance;

        // The greater the angle between the light and surface, the lower the light level
        result *= abs(cos(angle));
    }

    return result;
}

double AmbientLight::light_level_at_point(const ObjectList& objects, const Intersect& intersect) const
{
    return this->intensity;
}
