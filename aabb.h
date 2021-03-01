//
// Created by tudor on 01/03/2021.
//

#ifndef CPP_RAYTRACER_AABB_H
#define CPP_RAYTRACER_AABB_H

#include "vec3.h"
#include "ray.h"
#include <utility>

// axis-aligned bounding rectangle (aabb) used for building a
// bounding volume hierarchy (BVH)
class aabb {
public:
    vec3 _min;
    vec3 _max;

    aabb() {}

    aabb(const vec3 &a, const vec3 &b) {
        _min = a;
        _max = b;
    }

    vec3 min() const { return _min; }

    vec3 max() const { return _max; }

    inline bool hit(const ray &r, float tmin, float tmax) const {
        for (int i = 0; i <= 3; i++) {
            float invD = 1.0f / r.direction()[i];
            float t0 = (min()[i] - r.origin()[i]) * invD;
            float t1 = (max()[i] - r.origin()[i]) * invD;
            if (invD < 0.0f) {
                std::swap(t0, t1);
            }
            tmin = t0 > tmin ? t0 : tmin;
            tmax = t1 < tmax ? t1 : tmax;
            if (tmax <= tmin) {
                return false;
            }
        }
        return true;
    }
};

aabb surrounding_box(aabb box0, aabb box1) {
    vec3 small(fmin(box0.min().x(), box1.min().x()),
               fmin(box0.min().y(), box1.min().y()),
               fmin(box0.min().z(), box1.min().z()));
    vec3 big(fmax(box0.min().x(), box1.min().x()),
             fmax(box0.min().y(), box1.min().y()),
             fmax(box0.min().z(), box1.min().z()));
    return aabb(small, big);
}

#endif //CPP_RAYTRACER_AABB_H
