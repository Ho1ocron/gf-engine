#pragma once

namespace mymath {
    /*
    Creates a 2D vector with x and y components.
    */
    struct Vector2 
    {
    public:
        double x;
        double y;

        bool operator==(const Vector2& other) const;
        bool operator!=(const Vector2& other) const;

        Vector2 operator+(const Vector2& other) const;
        Vector2 operator-(const Vector2& other) const;
        Vector2 operator*(const double& scalar) const;
        Vector2 operator/(const double& scalar) const;

        Vector2& operator+=(const Vector2& other);
        Vector2& operator-=(const Vector2& other);
        Vector2& operator*=(const double& scalar);
        Vector2& operator/=(const double& scalar);

        void normalize();
        double length() const;
        
        Vector2(const double& x, const double& y) : x(x), y(y) {}
        ~Vector2() = default;
    };
} // namespace mymath