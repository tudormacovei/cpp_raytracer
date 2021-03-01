//
// Created by tudor on 17/02/2021.
//

#ifndef HITABLE_H
#define HITABLE_H

#include "ray.h"
#include "material.h"
#include "aabb.h"

struct hit_record {
    float t;    // parameter of the ray that hit, defines the hitpoint
    vec3 p;     // incoming
    vec3 normal;
    material *mat_ptr;
};

class hitable {
public:
    virtual bool hit(const ray &r, float t_min, float t_max, hit_record &rec) const = 0;

    virtual bool bounding_box(float t0, float t1, aabb &box) const = 0;
};


#endif //HITABLE_H
