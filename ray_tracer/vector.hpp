#pragma once

#include "math_extension.hpp"
#include <vector>

class Vector {

public:

    double x;
    double y;
    double z;
    
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

double vec_dot_product(const Vector& A, const Vector& B);
double vec_anglebetween_rad(const Vector& A, const Vector& B);
double vec_distance(const Vector& A, const Vector& B);

class Ray {

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

class Color {

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
    Color(const Vector& vec)
    {
        this->red = (int)vec.x;
        this->green = (int)vec.y;
        this->blue = (int)vec.z;
    }

    void operator+=(const Color& B);
    void operator-=(const Color& B);
    void operator*=(const double B);

    operator int() const;

    void abs_col();

};
#define BLACK { 0x00, 0x00, 0x00 }
#define WHITE { 0xFF, 0xFF, 0xFF }
#define RED { 0xFF, 0x00, 0x00 }
#define GREEN { 0x00, 0xFF, 0x00 }
#define BLUE { 0x00, 0x00, 0xFF }

Color operator+(const Color& A, const Color& B);
Color operator-(const Color& A, const Color& B);
Color operator*(const Color& A, const double B);
Color operator/(const Color& A, const double B);

Color color_diff(const Color& A, const Color& B);
