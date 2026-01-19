#pragma once

namespace mymath {
    /*
    Creates a 3D vector with x, y, and z components.
    */
    struct Vector3
    {
    public:
        double x;
        double y;
        double z;

        bool operator==(const Vector3& other) const;
        bool operator!=(const Vector3& other) const;

        Vector3 operator+(const Vector3& other) const;
        Vector3 operator-(const Vector3& other) const;
        Vector3 operator*(const double& scalar) const;
        Vector3 operator/(const double& scalar) const;

        Vector3& operator+=(const Vector3& other);
        Vector3& operator-=(const Vector3& other);
        Vector3& operator*=(const double& scalar);
        Vector3& operator/=(const double& scalar);

        void normalize();
        double length() const;
        
        Vector3(const double& x, const double& y, const double& z) : x(x), y(y), z(z) {}
        ~Vector3() = default;
    };
} // namespace mymath