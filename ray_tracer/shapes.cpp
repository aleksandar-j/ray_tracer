
#include "shapes.hpp"

Vector Vector::operator+(Vector B)
{
    return Vector(this->x + B.x, this->y + B.y, this->z + B.z);
}

Vector Vector::operator-(Vector B)
{
    return Vector( this->x - B.x, this->y - B.y, this->z - B.z );
}

Vector Vector::operator*(Vector B)
{
    return Vector(this->x * B.x, this->y * B.y, this->z * B.z);
}

Vector Vector::operator/(Vector B)
{
    return Vector(this->x / B.x, this->y / B.y, this->z / B.z);
}

void Vector::operator*=(double B)
{
    this->x *= B;
    this->y *= B;
    this->z *= B;
}

double Vector::magnitude()
{
    return sqrt(this->x*this->x + this->y*this->y + this->z*this->z);
}

Vector Vector::get_unit_vector()
{
    double mag = this->magnitude();
    return Vector(this->x / mag, this->y / mag, this->z / mag);
}

void Vector::make_unit_vector()
{
    double magnitude = this->magnitude();

    this->x /= magnitude;
    this->y /= magnitude;
    this->z /= magnitude;
}


double vec_dot_product(Vector A, Vector B)
{
    return A.x*B.x + A.y*B.y + A.z*B.z;
}

double vec_distance(Vector A, Vector B)
{
    return sqrt((A.x - B.x)*(A.x - B.x) + (A.y - B.y)*(A.y - B.y) + (A.z - B.z)*(A.z - B.z));
}
