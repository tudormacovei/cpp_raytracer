//
// Created by tudor on 16/02/2021.
//

#include "vec3.h"

#include <cmath>
#include <cstdlib>
#include <iostream>

inline std::istream& operator>>(std::istream &is, vec3 &t) {
    // e[3] is not a public variable
    float temp;
    is >> temp;
    t.set_x(temp);
    is >> temp;
    t.set_y(temp);
    is >> temp;
    t.set_z(temp);
    return is;
}

inline std:: ostream& operator<<(std::ostream &os, const vec3 &t) {
    os << t.x() << " " << t.y() << " " << t.z();
    return os;
}

inline vec3 operator+(const vec3 &v1, const vec3 &v2) {
    return vec3(v1.x() + v2.x(), v1.y() + v2.y(), v1.z() + v2.z());
}

inline vec3 operator-(const vec3 &v1, const vec3 &v2) {
    return vec3(v1.x() - v2.x(), v1.y() - v2.y(), v1.z() - v2.z());
}

inline vec3 operator*(const vec3 &v1, const vec3 &v2) {
    return vec3(v1.x() * v2.x(), v1.y() * v2.y(), v1.z() * v2.z());
}

inline vec3 operator/(const vec3 &v1, const vec3 &v2) {
    return vec3(v1.x() / v2.x(), v1.y() / v2.y(), v1.z() / v2.z());
}

inline vec3 operator*(const vec3 &v, float a) {
    return vec3(a * v.x(), a * v.y(), a * v.z());
}

// and mirrored
inline vec3 operator*(float a, const vec3 &v) {
    return vec3(a * v.x(), a * v.y(), a * v.z());
}

inline vec3 operator/(const vec3 &v, float a) {
    return vec3(a / v.x(), a / v.y(), a / v.z());
}

inline float  dot(const vec3 &v1, const vec3 &v2) {
    return v1.x() * v2.x() + v1.y() * v2.y() + v1.z() * v2.z();
}

inline vec3 cross(const vec3 &v1, const vec3 &v2) {
    return vec3( (v1.y() * v2.z() - v1.z() * v2.y()),
                 (-(v1.x()*v2.z() - v1.z()*v2.x())),
                 (v1.x()*v2.y() - v1.y()*v2.x()));
}

inline vec3& vec3::operator+=(const vec3&v) {
    e[0] += v.x();
    e[1] += v.y();
    e[2] += v.z();
    return *this;
}

inline vec3& vec3::operator*=(const vec3 &v) {
    e[0] *= v.x();
    e[1] *= v.y();
    e[2] *= v.z();
    return *this;
}

inline vec3& vec3::operator*=(const float a) {
    e[0] *= a;
    e[1] *= a;
    e[2] *= a;
    return *this;
}

inline vec3& vec3::operator/=(const vec3 &v) {
    e[0] /= v.x();
    e[1] /= v.y();
    e[2] /= v.z();
    return *this;
}

inline vec3& vec3::operator/=(const float t) {
    float k = 1.0/t;

    e[0] *= k;
    e[1] *= k;
    e[2] *= k;
    return *this;
}

inline vec3& vec3::operator-=(const vec3& v) {
    e[0] -= v.x();
    e[1] -= v.y();
    e[2] -= v.z();
    return *this;
}

inline vec3 unit_vector(vec3 v) {
    return v / v.length();
}