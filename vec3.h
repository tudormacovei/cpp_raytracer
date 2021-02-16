//
// Created by tudor on 16/02/2021.
//

#ifndef UNTITLED_VEC3_H
#define UNTITLED_VEC3_H


#include <cmath>

class vec3 {
private:
    float e[3];
public:
    vec3() {}
    vec3 (float e0, float e1, float e2) {
        e[0] = e0;
        e[1] = e1;
        e[2] = e2;
    }
    inline void set_x (float x) { e[0] = x; };
    inline void set_y (float x) { e[1] = x; };
    inline void set_z (float x) { e[2] = x; };
    // when using class for vectors
    inline float x() const { return e[0]; }
    inline float y() const { return e[1]; }
    inline float z() const { return e[2]; }
    // when using class for color
    inline float r() const { return e[0]; }
    inline float g() const { return e[1]; }
    inline float b() const { return e[2]; }

    inline const vec3& operator+() const { return *this; }
    inline vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
    inline float operator[] (int i) const { return e[i]; }
    inline float& operator[](int i) { return e[i]; }

    inline vec3& operator+=(const vec3 &v2);
    inline vec3& operator-=(const vec3 &v2);
    inline vec3& operator*=(const vec3 &v2);
    inline vec3& operator/=(const vec3 &v2);
    inline vec3& operator*=(const float t);
    inline vec3& operator/=(const float t);

    inline float length() const {
        return sqrt(e[0]*e[0] + e[1]*e[1] + e[2]*e[2]);
    }

    inline float squared_length() const {
        return e[0]*e[0] + e[1]*e[1] + e[2]*e[2];
    }

    inline void make_unit_vector() {
        float k = 1.0 / squared_length();
    }
};


#endif //UNTITLED_VEC3_H
