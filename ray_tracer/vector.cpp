
#include "vector.hpp"

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

double vec_dot_product(const Vector& A, const Vector& B)
{
    return A.x*B.x + A.y*B.y + A.z*B.z;
}

double vec_distance(const Vector& A, const Vector& B)
{
    return sqrt((A.x - B.x)*(A.x - B.x) + (A.y - B.y)*(A.y - B.y) + (A.z - B.z)*(A.z - B.z));
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

Color operator+(const Color& A, const Color& B)
{
    return { A.red + B.red, A.green + B.green, A.blue + B.blue };
}
Color operator-(const Color& A, const Color& B)
{
    return { A.red - B.red, A.green - B.green, A.blue - B.blue };
}
Color operator*(const Color& A, const double B)
{
    return { (int)(A.red * B), (int)(A.green * B), (int)(A.blue * B) };
}
Color operator/(const Color& A, const double B)
{
    return { (int)(A.red / B), (int)(A.green / B), (int)(A.blue / B) };
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
