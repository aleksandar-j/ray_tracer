
#include "shapes.hpp"

bool Vector::operator==(const Vector& B) const
{
    return (this->x == B.x && this->y == B.y && this->z == B.z);
}

bool Vector::operator!=(const Vector& B) const
{
    return (!(*this == B));
}

Vector Vector::operator+(const Vector& B) const
{
    return { this->x + B.x, this->y + B.y, this->z + B.z };
}

Vector Vector::operator+(const double B) const
{
    return { this->x + B, this->y + B, this->z + B };
}

Vector Vector::operator-(const Vector& B) const
{
    return { this->x - B.x, this->y - B.y, this->z - B.z };
}

Vector Vector::operator-(const double B) const
{
    return { this->x - B, this->y - B, this->z - B };
}

Vector Vector::operator*(const Vector& B) const
{
    return { this->x * B.x, this->y * B.y, this->z * B.z };
}

Vector Vector::operator*(const double B) const
{
    return { this->x * B, this->y * B, this->z * B };
}

Vector Vector::operator/(const Vector& B) const
{
    return { this->x / B.x, this->y / B.y, this->z / B.z };
}

Vector Vector::operator/(const double B) const
{
    return { this->x / B, this->y / B, this->z / B };
}

void Vector::operator+=(const Vector& B)
{
    *this = *this + B;
}

void Vector::operator+=(const double B)
{
    *this = *this + B;
}

void Vector::operator-=(const Vector& B)
{
    *this = *this - B;
}

void Vector::operator*=(const double B)
{
    *this = *this * B;
}

double Vector::magnitude() const
{
    return sqrt(this->x*this->x + this->y*this->y + this->z*this->z);
}

Vector Vector::get_unit_vector() const
{
    double mag = this->magnitude();
    return { this->x / mag, this->y / mag, this->z / mag };
}

void Vector::make_unit_vector()
{
    double magnitude = this->magnitude();

    this->x /= magnitude;
    this->y /= magnitude;
    this->z /= magnitude;
}


double vec_dot_product(const Vector& A, const Vector& B)
{
    return A.x*B.x + A.y*B.y + A.z*B.z;
}

double vec_distance(const Vector& A, const Vector& B)
{
    return sqrt((A.x - B.x)*(A.x - B.x) + (A.y - B.y)*(A.y - B.y) + (A.z - B.z)*(A.z - B.z));
}


Color::operator uint32_t() const
{
    uint32_t new_red = this->red << 16;
    uint32_t new_green = this->green << 8;
    uint32_t new_blue = this->blue;

    return new_red | new_green | new_blue;
}


std::pair<double, Color> Rect::ray_intersect(const Ray& ray) const
{
    return { std::numeric_limits<double>::max(), BLACK };
}

std::pair<double, Color> Sphere::ray_intersect(const Ray& ray) const
{
    Vector cam_to_center{ this->center - ray.origin };
    double dist_cam_to_center = cam_to_center.magnitude();
    double dist_cam_from_center_normal = vec_dot_product(cam_to_center, ray.direction);

    double dist_ray_from_center = 
        sqrt(dist_cam_to_center*dist_cam_to_center - dist_cam_from_center_normal*dist_cam_from_center_normal);
    if (dist_ray_from_center > this->radius) {
        return { std::numeric_limits<double>::max(), BLACK };
    }

    double dist_from_intersections = 2 * sqrt(this->radius*this->radius - dist_ray_from_center*dist_ray_from_center);

    double dist_cam_to_intersec_1 = dist_cam_from_center_normal - dist_from_intersections / 2;
    double dist_cam_to_intersec_2 = dist_cam_from_center_normal + dist_from_intersections / 2;

    if (dist_cam_to_intersec_1 > 0 || dist_cam_to_intersec_2 > 0) {
        if (dist_cam_to_intersec_1 > 0 && dist_cam_to_intersec_1 < dist_cam_to_intersec_2) {
            return { std::numeric_limits<double>::max() - dist_cam_to_intersec_1, this->color };
        } else {
            return { std::numeric_limits<double>::max() - dist_cam_to_intersec_2, this->color };
        }
    } else {
        return { std::numeric_limits<double>::max(), BLACK };
    }
}


Ray Camera::get_ray_on_pixel(int x, int y)
{
    Vector point_on_viewport = camrect_xy_start_point;

    point_on_viewport += camrect_width_ray.direction * (camrect_width_per_pixel * x) + 
                                                                    (camrect_width_per_pixel / 2);
    point_on_viewport += camrect_height_ray.direction * (camrect_height_per_pixel * y) + 
                                                                    (camrect_height_per_pixel / 2);

    return Ray{ this->position, point_on_viewport - this->position };
}
