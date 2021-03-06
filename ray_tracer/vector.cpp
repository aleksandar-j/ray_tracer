
#include "vector.hpp"

Vector::Vector()
{
}
Vector::Vector(const double x, const double y, const double z) 
    :
    x(x), y(y), z(z)
{
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

bool operator==(const Vector& A, const Vector& B)
{
    return A.x == B.x && A.y == B.y && A.z == B.z;
}
bool operator!=(const Vector& A, const Vector& B)
{
    return !(A == B);
}

Vector operator-(const Vector& A)
{
    return { -A.x, -A.y, -A.z };
}

Vector operator+(const Vector& A, const Vector& B)
{
    return { A.x + B.x, A.y + B.y, A.z + B.z };
}
Vector operator+(const Vector& A, const double B)
{
    return { A.x + B, A.y + B, A.z + B };
}
Vector operator-(const Vector& A, const Vector& B)
{
    return { A.x - B.x, A.y - B.y, A.z - B.z };
}
Vector operator-(const Vector& A, const double B)
{
    return { A.x - B, A.y - B, A.z - B };
}
Vector operator*(const Vector& A, const Vector& B)
{
    return { A.x * B.x, A.y * B.y, A.z * B.z };
}
Vector operator*(const Vector& A, const double B)
{
    return { A.x * B, A.y * B, A.z * B };
}
Vector operator/(const Vector& A, const Vector& B)
{
    return { A.x / B.x, A.y / B.y, A.z / B.z };
}
Vector operator/(const Vector& A, const double B)
{
    return { A.x / B, A.y / B, A.z / B };
}

Vector get_unit_vector(const Vector& A)
{
    double mag = A.magnitude();
    return { A.x / mag, A.y / mag, A.z / mag };
}

Vector vec_rotate_x_deg(const Vector& A, const double deg)
{
    Vector result = A;
    result.rotate_x_deg(deg);
    return result;
}

Vector vec_rotate_y_deg(const Vector & A, const double deg)
{
    Vector result = A;
    result.rotate_y_deg(deg);
    return result;
}

Vector vec_rotate_z_deg(const Vector & A, const double deg)
{
    Vector result = A;
    result.rotate_z_deg(deg);
    return result;
}

double vec_dot_product(const Vector& A, const Vector& B)
{
    return A.x*B.x + A.y*B.y + A.z*B.z;
}

double vec_anglebetween_rad(const Vector& A, const Vector& B)
{
    return acos(vec_dot_product(A, B) / (A.magnitude() * B.magnitude()));
}

double vec_distance(const Vector& A, const Vector& B)
{
    return sqrt((A.x - B.x)*(A.x - B.x) + (A.y - B.y)*(A.y - B.y) + (A.z - B.z)*(A.z - B.z));
}

Vector rand_unit_vector()
{
    double rand_x = (rand() / (double)RAND_MAX) * 2 - 1.0;
    double rand_y = (rand() / (double)RAND_MAX) * 2 - 1.0;
    double rand_z = (rand() / (double)RAND_MAX) * 2 - 1.0;

    return get_unit_vector({ rand_x, rand_y, rand_z });
}

Ray::Ray() 
{
}
Ray::Ray(const Vector& origin, const Vector& direction) 
    :
    origin(origin), direction(direction)
{
    this->direction.make_unit_vector();
}
