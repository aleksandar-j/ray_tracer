
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

double Vector::magnitude()
{
    if (this->mag == 0) {
        this->mag = sqrt(this->x*this->x + this->y*this->y + this->z*this->z);
    }
    return this->mag;
}

Vector Vector::get_unit_vector()
{
    double mag = this->magnitude();
    return { this->x / mag, this->y / mag, this->z / mag };
}

void Vector::make_unit_vector()
{
    double mag = this->magnitude();

    this->x /= mag;
    this->y /= mag;
    this->z /= mag;
}

void Vector::rotate_x_deg(const double deg)
{
    double mag = this->magnitude();

    this->x /= mag;
    this->x = cos(acos(this->x) + deg_to_rad(deg));
    this->x *= mag;
}

void Vector::rotate_y_deg(const double deg)
{
    double mag = this->magnitude();

    this->y /= mag;
    this->y = cos(acos(this->y) + deg_to_rad(deg));
    this->y *= mag;
}

void Vector::rotate_z_deg(const double deg)
{
    double mag = this->magnitude();

    this->z /= mag;
    this->z = cos(acos(this->z) + deg_to_rad(deg));
    this->z *= mag;
}


double vec_dot_product(const Vector& A, const Vector& B)
{
    return A.x*B.x + A.y*B.y + A.z*B.z;
}

double vec_distance(const Vector& A, const Vector& B)
{
    return sqrt((A.x - B.x)*(A.x - B.x) + (A.y - B.y)*(A.y - B.y) + (A.z - B.z)*(A.z - B.z));
}


Color Color::operator+(const Color& B) const
{
    return { this->red + B.red, this->green + B.green, this->blue + B.blue };
}

Color Color::operator-(const Color& B) const
{
    return { this->red - B.red, this->green - B.green, this->blue - B.blue };
}

Color Color::operator*(const double B) const
{
    return { (int)(this->red * B), (int)(this->green * B), (int)(this->blue * B) };
}

Color Color::operator/(const double B) const
{
    return { (int)(this->red / B), (int)(this->green / B), (int)(this->blue / B) };
}

void Color::operator+=(const Color& B)
{
    this->red += B.red;
    this->green += B.green;
    this->blue += B.blue;
}

void Color::operator-=(const Color& B)
{
    this->red -= B.red;
    this->green -= B.green;
    this->blue -= B.blue;
}

Color::operator int() const
{
    int new_red = this->red << 16;
    int new_green = this->green << 8;
    int new_blue = this->blue;

    return new_red | new_green | new_blue;
}

void Color::abs_col()
{
    this->red = abs(this->red);
    this->green = abs(this->green);
    this->blue = abs(this->blue);
}

Color color_diff(const Color& A, const Color& B)
{
    Color new_color;

    new_color.red = abs(A.red - B.red);
    new_color.green = abs(A.green - B.green);
    new_color.blue = abs(A.blue - B.blue);

    return new_color;
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


Ray Camera::get_ray_on_pixel(int x, int y)
{
    Vector point_on_viewport = camrect_xy_start_point;

    point_on_viewport += camrect_width_ray.direction * (camrect_width_per_pixel * (x+1)) - 
                                                                    (camrect_width_per_pixel / 2);
    point_on_viewport += camrect_height_ray.direction * (camrect_height_per_pixel * (y+1)) - 
                                                                    (camrect_height_per_pixel / 2);

    return { this->position, point_on_viewport - this->position };
}

Ray Camera::get_ray_on_pixel_rand(int x, int y)
{
    Vector point_on_viewport = camrect_xy_start_point;

    double rand_x = (double)(rand() % (int)(camrect_width_per_pixel * 10000)) / 10000.0;
    double rand_y = (double)(rand() % (int)(camrect_width_per_pixel * 10000)) / 10000.0;

    point_on_viewport += camrect_width_ray.direction * (camrect_width_per_pixel * (x + 1)) - rand_x;
    point_on_viewport += camrect_height_ray.direction * (camrect_height_per_pixel * (y + 1)) - rand_y;

    return { this->position, point_on_viewport - this->position };
}
