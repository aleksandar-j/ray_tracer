#pragma once

#include "math_extension.hpp"

class Vector {

public:
    double x;
    double y;
    double z;

    Vector() {}
    Vector(double x, double y) :
        x(x), y(y)
    {
        this->z = 0;
    }
    Vector(double x, double y, double z) :
        x(x), y(y), z(z)
    {
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

};

bool operator==(const Vector& A, const Vector& B);
bool operator!=(const Vector& A, const Vector& B);

Vector operator+(const Vector& A, const Vector& B);
Vector operator+(const Vector& A, const double B);
Vector operator-(const Vector& A, const Vector& B);
Vector operator-(const Vector& A, const double B);
Vector operator*(const Vector& A, const Vector& B);
Vector operator*(const Vector& A, const double B);
Vector operator/(const Vector& A, const Vector& B);
Vector operator/(const Vector& A, const double B);

Vector get_unit_vector(const Vector& A);
double vec_dot_product(const Vector& A, const Vector& B);
double vec_distance(const Vector& A, const Vector& B);

class Ray : public Vector {

public:
    Vector origin;
    Vector direction;

    Ray() {}
    Ray(const Vector& origin, const Vector& direction) :
        origin(origin), direction(direction)
    {
        this->direction.make_unit_vector();
    }

};


class Color : public Vector {

public:
    int red;
    int green;
    int blue;

    Color() {}
    Color(const int red, const int green, const int blue) :
        red(red), green(green), blue(blue)
    {
    }
    Color(const int argb)
    {
        this->red = (argb & 0x00FF0000) >> 16;
        this->green = (argb & 0x0000FF00) >> 8;
        this->blue = (argb & 0x000000FF) >> 0;
    }

    Color operator+(const Color& B) const;
    Color operator-(const Color& B) const;
    Color operator*(const double B) const;
    Color operator/(const double B) const;

    void operator+=(const Color& B);
    void operator-=(const Color& B);

    operator int() const;

    void abs_col();

};
#define BLACK { 0x0, 0x0, 0x0 }
#define WHITE { 0xFF, 0xFF, 0xFF }

Color color_diff(const Color& A, const Color& B);
