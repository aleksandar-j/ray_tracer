
#include "texture.hpp"

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

void Color::operator*=(const double B)
{
    this->red *= B;
    this->green *= B;
    this->blue *= B;
}

void Color::operator/=(const double B)
{
    this->red /= B;
    this->green /= B;
    this->blue /= B;
}

Color::operator int() const
{
    int new_red = (int)this->red << 16;
    int new_green = (int)this->green << 8;
    int new_blue = (int)this->blue << 0;

    return new_red | new_green | new_blue;
}

void Color::make_grey()
{
    double avg = (this->red + this->green + this->blue) / 3.0;

    this->red = avg;
    this->green = avg;
    this->blue = avg;
}

bool Color::is_valid() const
{
    bool valid_red = this->red <= 255.0 && this->red >= 0.0;
    bool valid_green = this->green <= 255.0 && this->green >= 0.0;
    bool valid_blue = this->blue <= 255.0 && this->blue >= 0.0;

    return valid_red && valid_green && valid_blue;
}


Color operator+(const Color& A, const Color& B)
{
    return { A.red + B.red, A.green + B.green, A.blue + B.blue };
}
Color operator-(const Color& A, const Color& B)
{
    return { A.red - B.red, A.green - B.green, A.blue - B.blue };
}
Color operator*(const Color& A, const Color& B)
{
    return { A.red * B.red, A.green * B.green, A.blue * B.blue };
}
Color operator*(const Color& A, const double B)
{
    return { A.red * B, A.green * B, A.blue * B };
}
Color operator/(const Color& A, const double B)
{
    return { A.red / B, A.green / B, A.blue / B };
}

Color color_safe_add(const Color& A, const Color& B)
{
    Color result = A + B;

    result.red = (result.red > 255.0) ? 255.0 : result.red;
    result.green = (result.green > 255.0) ? 255.0 : result.green;
    result.blue = (result.blue > 255.0) ? 255.0 : result.blue;

    return result;
}

Color color_safe_multiply(const Color& A, const double B)
{
    Color result = A * B;

    result.red = (result.red > 255.0) ? 255.0 : result.red;
    result.green = (result.green > 255.0) ? 255.0 : result.green;
    result.blue = (result.blue > 255.0) ? 255.0 : result.blue;

    return result;
}

Color color_get_grey(Color A)
{
    A.make_grey();
    return A;
}

Color color_mix_weights(const Color& A, double A_weight, const Color& B, double B_weight)
{
    if (A_weight + B_weight > 1.0) {
        double sum = A_weight + B_weight;

        A_weight /= sum;
        B_weight /= sum;
    }

    return A*A_weight + B*B_weight;
}

Color color_diff(const Color& A, const Color& B)
{
    Color new_color;

    new_color.red = abs(A.red - B.red);
    new_color.green = abs(A.green - B.green);
    new_color.blue = abs(A.blue - B.blue);

    return new_color;
}

double color_greatest_diff(const Color& A, const Color& B)
{
    Color diff = color_diff(A, B);
    return std::fmax(diff.blue, (std::fmax(diff.red, diff.green)));
}

double color_average_diff(const Color & A, const Color & B)
{
    Color diff = color_diff(A, B);
    return (diff.red + diff.green + diff.blue) / 3.0;
}
