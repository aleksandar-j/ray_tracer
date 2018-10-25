
#include "shapes.hpp"

bool Vector::operator==(const Vector B) const
{
    return (this->x == B.x && this->y == B.y && this->z == B.z);
}

bool Vector::operator!=(const Vector B) const
{
    return (!(*this == B));
}

Vector Vector::operator+(const Vector B) const
{
    return { this->x + B.x, this->y + B.y, this->z + B.z };
}

Vector Vector::operator+(const double B) const
{
    return { this->x + B, this->y + B, this->z + B };
}

Vector Vector::operator-(const Vector B) const
{
    return { this->x - B.x, this->y - B.y, this->z - B.z };
}

Vector Vector::operator-(const double B) const
{
    return { this->x - B, this->y - B, this->z - B };
}

Vector Vector::operator*(const Vector B) const
{
    return { this->x * B.x, this->y * B.y, this->z * B.z };
}

Vector Vector::operator*(const double B) const
{
    return { this->x * B, this->y * B, this->z * B };
}

Vector Vector::operator/(const Vector B) const
{
    return { this->x / B.x, this->y / B.y, this->z / B.z };
}

Vector Vector::operator/(const double B) const
{
    return { this->x / B, this->y / B, this->z / B };
}

void Vector::operator+=(const Vector B)
{
    *this = *this + B;
}

void Vector::operator+=(const double B)
{
    *this = *this + B;
}

void Vector::operator-=(const Vector B)
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


double vec_dot_product(const Vector A, const Vector B)
{
    return A.x*B.x + A.y*B.y + A.z*B.z;
}

double vec_distance(const Vector A, const Vector B)
{
    return sqrt((A.x - B.x)*(A.x - B.x) + (A.y - B.y)*(A.y - B.y) + (A.z - B.z)*(A.z - B.z));
}


bool Rect::ray_intersect(const Ray ray) const
{
    return false;
}

bool Sphere::ray_intersect(const Ray ray) const
{
    Vector cam_to_center{ this->center - ray.origin };
    double dist_cam_to_center = cam_to_center.magnitude();
    double dist_cam_from_center_normal = vec_dot_product(cam_to_center, ray.direction);

    double dist_ray_from_center = 
        sqrt(dist_cam_to_center*dist_cam_to_center - dist_cam_from_center_normal*dist_cam_from_center_normal);
    if (dist_ray_from_center > this->radius) {
        return false;
    } else {
        return true;
    }
}


Vector Camera::get_vec_on_pixel(int x, int y)
{
    Vector result = camrect_xy_start_point;
    result += camrect_width_ray.direction * (camrect_width_per_pixel * x) + (camrect_width_per_pixel / 2);
    result += camrect_height_ray.direction * (camrect_height_per_pixel * y) + (camrect_height_per_pixel / 2);

    return result;
}
