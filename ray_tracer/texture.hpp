#pragma once

#include "vector.hpp"

class Texture {

public:


};

class Color {

public:
    Color()
    {
        this->red = 0.0;
        this->green = 0.0;
        this->blue = 0.0;
    }
    Color(const double red, const double green, const double blue) :
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
        this->red = vec.x;
        this->green = vec.y;
        this->blue = vec.z;
    }

    void operator+=(const Color& B);
    void operator-=(const Color& B);
    void operator*=(const double B);
    void operator/=(const double B);

    operator int() const;

    void make_grey();

    bool is_valid() const;

    // Valid values range [0-255]
    double red;
    double green;
    double blue;

};
// Common colors
#define BLACK { 0.0, 0.0, 0.0 }
#define WHITE { 255.0, 255.0, 255.0 }
#define GRAY { 128.0, 128.0, 128.0 }

#define RED { 255.0, 0.0, 0.0 }
#define GREEN { 0.0, 255.0, 0.0 }
#define BLUE { 0.0, 0.0, 255.0 }

#define MAROON { 128.0, 0.0, 0.0 }

Color operator+(const Color& A, const Color& B);
Color operator-(const Color& A, const Color& B);
Color operator*(const Color& A, const Color& B);
Color operator*(const Color& A, const double B);
Color operator/(const Color& A, const double B);

Color color_diff(const Color& A, const Color& B);
double color_greatest_diff(const Color& A, const Color& B);
double color_average_diff(const Color& A, const Color& B);
