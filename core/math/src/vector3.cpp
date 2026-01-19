#include <cmath>
#include "vector3.h"



namespace mymath {
bool Vector3::operator==(const Vector3& other) const {
    return x == other.x && y == other.y && z == other.z;
}


bool Vector3::operator!=(const Vector3& other) const {
    return !(*this == other);
}


Vector3 Vector3::operator+(const Vector3& other) const {
    return Vector3{x + other.x, y + other.y, z + other.z};
}


Vector3 Vector3::operator-(const Vector3& other) const {
    return Vector3{x - other.x, y - other.y, z - other.z};
}


Vector3 Vector3::operator*(const double& scalar) const {
    return Vector3{x * scalar, y * scalar, z * scalar};
}


Vector3 Vector3::operator/(const double& scalar) const {
    return Vector3{x / scalar, y / scalar, z / scalar};
}


Vector3& Vector3::operator+=(const Vector3& other) {
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

Vector3& Vector3::operator-=(const Vector3& other) {
    x -= other.x;
    y -= other.y;
    z -= other.z;
    return *this;
}

Vector3& Vector3::operator*=(const double& scalar) {
    x *= scalar;
    y *= scalar;
    z *= scalar;
    return *this;
}


Vector3& Vector3::operator/=(const double& scalar) {
    x /= scalar;
    y /= scalar;
    z /= scalar;
    return *this;
}


double Vector3::length() const {
    return std::sqrt(x * x + y * y + z * z);
}


void Vector3::normalize() {
    double len = length();
    if (len > 0) {
        x /= len;
        y /= len;
        z /= len;
    }
}
} // namespace mymath