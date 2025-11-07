#pragma once
#include <algorithm>
#include <cassert>
#include <ostream>

// 2D Vector stuff

// Used for operations in 2D space
struct vec2 {
    double x, y;

    vec2()
        : x(0)
        , y(0)
    {
    }
    vec2(double X, double Y)
        : x(X)
        , y(Y)
    {
    }

    // Lets you access x/y using [0] or [1]
    double& operator[](int i)
    {
        assert(i >= 0 && i < 2);
        return (i == 0) ? x : y;
    }

    double operator[](int i) const
    {
        assert(i >= 0 && i < 2);
        return (i == 0) ? x : y;
    }
};

// Print vector
inline std::ostream& operator<<(std::ostream& os, const vec2& v)
{
    return os << "(" << v.x << ", " << v.y << ")";
}

// Basic arithmetic operators
inline vec2 operator+(const vec2& a, const vec2& b) { return vec2(a.x + b.x, a.y + b.y); }
inline vec2 operator-(const vec2& a, const vec2& b) { return vec2(a.x - b.x, a.y - b.y); }
inline vec2 operator*(const vec2& v, double s) { return vec2(v.x * s, v.y * s); }
inline vec2 operator*(double s, const vec2& v) { return s * v; }
inline vec2 operator/(const vec2& v, double s) { return vec2(v.x / s, v.y / s); }

// Dot product, gives a measure of alignment between two vectors
inline double dot(const vec2& a, const vec2& b) { return a.x * b.x + a.y * b.y; }

// Vector length (distance from origin)
inline double length(const vec2& v) { return std::sqrt(v.x * v.x + v.y * v.y); }

// Returns a unit vector (if same direction, length = 1)
inline vec2 normalized(const vec2& v)
{
    double L = length(v);
    return (L == 0.0) ? v : v / L;
}

// 3D Vector stuff

// Used for vertices and 3D math operations
struct vec3 {
    double x, y, z;

    vec3()
        : x(0)
        , y(0)
        , z(0)
    {
    }
    vec3(double X, double Y, double Z)
        : x(X)
        , y(Y)
        , z(Z)
    {
    }

    // Access x,y,z using [0], [1], [2]
    double& operator[](int i)
    {
        assert(i >= 0 && i < 3);
        if (i == 0)
            return x;
        if (i == 1)
            return y;
        return z;
    }

    double operator[](int i) const
    {
        assert(i >= 0 && i < 3);
        if (i == 0)
            return x;
        if (i == 1)
            return y;
        return z;
    }
};

// Print vector like (x, y, z)
inline std::ostream& operator<<(std::ostream& os, const vec3& v)
{
    return os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
}

// Basic arithmetic
inline vec3 operator+(const vec3& a, const vec3& b) { return vec3(a.x + b.x, a.y + b.y, a.z + b.z); }
inline vec3 operator-(const vec3& a, const vec3& b) { return vec3(a.x - b.x, a.y - b.y, a.z - b.z); }
inline vec3 operator*(const vec3& v, double s) { return vec3(v.x * s, v.y * s, v.z * s); }
inline vec3 operator*(double s, const vec3& v) { return v * s; }
inline vec3 operator/(const vec3& v, double s) { return vec3(v.x / s, v.y / s, v.z / s); }

// Dot product, gives how similar two directions are
inline double dot(const vec3& a, const vec3& b) { return (a.x * b.x) + (a.y * b.y) + (a.z * b.z); }

// Vector length in 3D
inline double length(const vec3& v) { return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z); }

// Normalize vector to length 1
inline vec3 normalized(const vec3& v)
{
    double L = length(v);
    return (L == 0.0) ? v : v / L;
}

// Cross product, it gives a vector perpendicular to both a and b
inline vec3 cross(const vec3& a, const vec3& b)
{
    return vec3(
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x);
}
