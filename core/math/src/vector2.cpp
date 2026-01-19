#include "vector2.h"
#include <cmath>


namespace mymath {

bool Vector2::operator==(const Vector2& other) const {
    return x == other.x && y == other.y;
}


bool Vector2::operator!=(const Vector2& other) const {
    return !(*this == other);
}


Vector2 Vector2::operator+(const Vector2& other) const {
    return Vector2{x + other.x, y + other.y};
}


Vector2 Vector2::operator-(const Vector2& other) const {
    return Vector2{x - other.x, y - other.y};
}

Vector2 Vector2::operator*(const double& scalar) const {
    return Vector2{x * scalar, y * scalar};
}


Vector2 Vector2::operator/(const double& scalar) const {
    return Vector2{x / scalar, y / scalar};
}


Vector2& Vector2::operator+=(const Vector2& other) {
    x += other.x;
    y += other.y;
    return *this;
}


Vector2& Vector2::operator-=(const Vector2& other) {
    x -= other.x;
    y -= other.y;
    return *this;
}


Vector2& Vector2::operator*=(const double& scalar) {
    x *= scalar;
    y *= scalar;
    return *this;
}


Vector2& Vector2::operator/=(const double& scalar) {
    x /= scalar;
    y /= scalar;
    return *this;
}

double Vector2::length() const {
    return std::sqrt(x * x + y * y);
}


void Vector2::normalize() {
    double len = length();
    if (len != 0) {
        x /= len;
        y /= len;
    }
}
}