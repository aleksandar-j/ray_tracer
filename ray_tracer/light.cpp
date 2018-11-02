
#include "light.hpp"

#include "objects_list.hpp"

PointLight::PointLight()
{
}
PointLight::PointLight(const Vector& center, const double intensity)
    :
    center(center)
{
    if (intensity < 0.0 || intensity > 1.0) {
        throw "Light intensity invalid, valid range is [0.0-1.0]";
    }

    this->intensity = intensity;
}
PointLight::PointLight(const Vector& center, const double intensity, const Color& light_color)
{
    if (intensity < 0.0 || intensity > 1.0) {
        throw "Light intensity invalid, valid range is [0.0-1.0]";
    }

    this->light_color = light_color;
    this->intensity = intensity;
}

double PointLight::light_level_at_point(const ObjectList& world, const Intersect& intersect) const
{
    double result = 1.0;

    // Atmospheres on light and object
    Atmosphere light_atmosphere = atmosphere_at_point(world, this->center);
    Atmosphere object_atmosphere = atmosphere_at_point(world, intersect.point);

    bool same_atmosperes;
    if (light_atmosphere.atmosphere_shape == object_atmosphere.atmosphere_shape) {
        same_atmosperes = true;
    } else {
        same_atmosperes = false;
    }

    // Distance between light and point hit
    double light_point_dist = vec_distance(this->center, intersect.point);

    if (same_atmosperes) {
        if (light_atmosphere.light_dropoff_intensity < light_point_dist) {
            // Even if we can hit the point, light is too weak there in this atmosphere
            return 0.0;
        }
    }

    // Direction from our point towards light and back
    Ray point_light_ray{ {this->center}, {this->center - intersect.point } };
    Ray light_point_ray{ {this->center}, { intersect.point - this->center } };

    // Angle between light and object hit, only if we are actually checking object
    double object_light_angle;
    Ray object_normal_ray;
    
    if (intersect.shape_hit != nullptr) {
        object_normal_ray = intersect.shape_hit->normal_ray_at_point(intersect.point);
        object_light_angle = vec_anglebetween_rad(object_normal_ray.direction, point_light_ray.direction);
    }

    for (auto& object : world.object_list) {
        // We check whether some other object blocks us from hitting the main one

        Intersect intersect_data = object->ray_intersect(light_point_ray);
        
        if (intersect_data.shape_hit == nullptr) {
            // Nothing is hit, continue
            continue;
        }
        
        if (intersect_data.ray_to_point_dist <= light_point_dist) {
            // We hit something that is closer than our point (or maybe our point)

            if (abs(light_point_dist - intersect_data.ray_to_point_dist) > 0.0001) {
                // We hit something else, point is dark

                result = 0.0;
                break;
            }
        }
    }

    if (result != 0.0) {
        // We do hit the point by direct light

        // The greater the distance between the light and surface, the lower the light level, depending on the atmosphere
        if (same_atmosperes) {
            // If the same atmosphere object surrounds source and point, we can calculate just based on distance

            double light_at_distance =
                (light_atmosphere.light_dropoff_intensity - light_point_dist) /
                light_atmosphere.light_dropoff_intensity;

            result *= light_at_distance;
        } else {
            // TODO: Complicated work of seeing all intermediary atmospheres and their interactions
        }

        // The greater the angle between the light and surface, the lower the light level
        if (intersect.shape_hit != nullptr) {
            double angle_mod = abs(cos(object_light_angle));
            result *= angle_mod;
        }
    } else {
        // We don't get hit by direct light

    }

    return result;
}
