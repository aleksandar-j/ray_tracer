#pragma once

#include "math_extension.hpp"

class Vector {

public:
    Vector()
    {
    }
    Vector(double x, double y, double z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    void operator+=(const Vector& B);
    void operator+=(const double B);
    void operator-=(const Vector& B);
    void operator*=(const double B);

    double magnitude() const;

    void make_unit_vector();

    void rotate_x_deg(const double deg);
    void rotate_y_deg(const double deg);
    void rotate_z_deg(const double deg);

    double x;
    double y;
    double z;

};

bool operator==(const Vector& A, const Vector& B);
bool operator!=(const Vector& A, const Vector& B);

Vector operator-(const Vector& A);

Vector operator+(const Vector& A, const Vector& B);
Vector operator+(const Vector& A, const double B);
Vector operator-(const Vector& A, const Vector& B);
Vector operator-(const Vector& A, const double B);
Vector operator*(const Vector& A, const Vector& B);
Vector operator*(const Vector& A, const double B);
Vector operator/(const Vector& A, const Vector& B);
Vector operator/(const Vector& A, const double B);

Vector get_unit_vector(const Vector& A);

Vector vec_rotate_x_deg(const Vector&A, const double deg);
Vector vec_rotate_y_deg(const Vector&A, const double deg);
Vector vec_rotate_z_deg(const Vector&A, const double deg);

Vector rand_unit_vector();

double vec_dot_product(const Vector& A, const Vector& B);
double vec_anglebetween_rad(const Vector& A, const Vector& B);
double vec_distance(const Vector& A, const Vector& B);

class Ray {

public:
    Ray() {}
    Ray(const Vector& origin, const Vector& direction) :
        origin(origin), direction(direction)
    {
        this->direction.make_unit_vector();
    }

    Vector origin;
    Vector direction;

};
