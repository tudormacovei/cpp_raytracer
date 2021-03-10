//
// Created by tudor on 10/03/2021.
//

#ifndef CPP_RAYTRACER_TEXTURE_H
#define CPP_RAYTRACER_TEXTURE_H


#include "vec3.h"

class texture {
public:
    virtual vec3 value(float u, float v, const vec3& p) const = 0;
};

class constant_texture : public texture {
private:
    vec3 color;
public:
    constant_texture() {}
    constant_texture(vec3 c) : color(c) {}
    virtual vec3 value(float u, float v, const vec3& p) const {
        return color;
    }
};


#endif //CPP_RAYTRACER_TEXTURE_H
