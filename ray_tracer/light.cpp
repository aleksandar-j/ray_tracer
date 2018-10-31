
#include "light.hpp"

#include "objects_list.hpp"

double PointLight::light_level_at_point(const ObjectList& objects, const Intersect& intersect) const
{
    double result = this->intensity;

    // Atmospheres on light and object
    Atmosphere light_atmosphere = get_atmosphere_at_point(objects, this->center);
    Atmosphere object_atmosphere = get_atmosphere_at_point(objects, intersect.point);

    bool same_atmosperes;
    if (light_atmosphere.atmosphere_shape == object_atmosphere.atmosphere_shape) {
        same_atmosperes = true;
    } else {
        same_atmosperes = false;
    }

    // Distance between light and point hit
    double lightpoint_dist = vec_distance(this->center, intersect.point);

    if (same_atmosperes) {
        if (light_atmosphere.light_dropoff_linear_intensity < lightpoint_dist) {
            // Even if we can hit the point, light is too weak there in this atmosphere
            return 0.0;
        }
    }

    // Angle between light and point hit normal
    Ray objectnormal_ray = intersect.shape_hit->normal_ray_at_point(intersect.point);
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

        // The greater the distance between the light and surface, the lower the light level, depending on the atmosphere
        if (same_atmosperes) {
            // If the same atmosphere object surrounds source and point, we can calculate just based on distance
            
            double light_at_distance =
                (light_atmosphere.light_dropoff_linear_intensity - lightpoint_dist) /
                        light_atmosphere.light_dropoff_linear_intensity;

            result *= light_at_distance;
        } else {
            // TODO: Complicated work of seeing all intermediary atmospheres and their interactions
        }

        // The greater the angle between the light and surface, the lower the light level
        result *= abs(cos(angle));
    }

    return result;
}
