//
// Created by tudor on 16/02/2021.
//

#ifndef VEC3_H
#define VEC3_H


#include <cmath>

class vec3 {
private:
    float e[3];
public:
    vec3() {}

    vec3(float e0, float e1, float e2) {
        e[0] = e0;
        e[1] = e1;
        e[2] = e2;
    }

    inline void set_x(float x) { e[0] = x; };

    inline void set_y(float x) { e[1] = x; };

    inline void set_z(float x) { e[2] = x; };

    // when using class for vectors
    inline float x() const { return e[0]; }

    inline float y() const { return e[1]; }

    inline float z() const { return e[2]; }

    // when using class for color
    inline float r() const { return e[0]; }

    inline float g() const { return e[1]; }

    inline float b() const { return e[2]; }

    inline const vec3 &operator+() const { return *this; }

    inline vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }

    inline float operator[](int i) const { return e[i]; }

    inline float &operator[](int i) { return e[i]; }

    inline vec3 &operator+=(const vec3 &v2);

    inline vec3 &operator-=(const vec3 &v2);

    inline vec3 &operator*=(const vec3 &v2);

    inline vec3 &operator/=(const vec3 &v2);

    inline vec3 &operator*=(const float t);

    inline vec3 &operator/=(const float t);

    inline float length() const {
        return sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
    }

    inline float squared_length() const {
        return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
    }

    inline void make_unit_vector() {
        float k = 1.0 / squared_length();
        e[0] *= k;
        e[1] *= k;
        e[2] *= k;
    }
};

inline std::istream &operator>>(std::istream &is, vec3 &t) {
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

inline std::ostream &operator<<(std::ostream &os, const vec3 &t) {
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

inline vec3 operator/(const vec3 &v, float a) {
    return vec3(v.x() / a, v.y() / a, v.z() / a);
}

inline vec3 operator*(const vec3 &v, float a) {
    return vec3(a * v.x(), a * v.y(), a * v.z());
}

// inverted positions, same as function above

inline vec3 operator*(float a, const vec3 &v) {
    return vec3(a * v.x(), a * v.y(), a * v.z());
}

inline float dot(const vec3 &v1, const vec3 &v2) {
    return v1.x() * v2.x() + v1.y() * v2.y() + v1.z() * v2.z();
}

inline vec3 cross(const vec3 &v1, const vec3 &v2) {
    return vec3((v1.y() * v2.z() - v1.z() * v2.y()),
                (-(v1.x() * v2.z() - v1.z() * v2.x())),
                (v1.x() * v2.y() - v1.y() * v2.x()));
}

inline vec3 &vec3::operator+=(const vec3 &v) {
    e[0] += v.x();
    e[1] += v.y();
    e[2] += v.z();
    return *this;
}

inline vec3 &vec3::operator*=(const vec3 &v) {
    e[0] *= v.x();
    e[1] *= v.y();
    e[2] *= v.z();
    return *this;
}

inline vec3 &vec3::operator*=(const float a) {
    e[0] *= a;
    e[1] *= a;
    e[2] *= a;
    return *this;
}

inline vec3 &vec3::operator/=(const vec3 &v) {
    e[0] /= v.x();
    e[1] /= v.y();
    e[2] /= v.z();
    return *this;
}

inline vec3 &vec3::operator/=(const float t) {
    float k = 1.0 / t;

    e[0] *= k;
    e[1] *= k;
    e[2] *= k;
    return *this;
}

inline vec3 &vec3::operator-=(const vec3 &v) {
    e[0] -= v.x();
    e[1] -= v.y();
    e[2] -= v.z();
    return *this;
}

inline vec3 unit_vector(vec3 v) {
    return v / v.length();
}

#endif //VEC3_H
