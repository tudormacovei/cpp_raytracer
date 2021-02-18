//
// Created by tudor on 18/02/2021.
//

#ifndef DIELECTRIC_H
#define DIELECTRIC_H

#include "material.h"
#include "helper_functions.h"

class dielectric:public material  {
public:
    float ref_idx;

    dielectric(float ri) : ref_idx(ri) {}

    virtual bool scatter(const ray& r_in, const hit_record &rec, vec3 &attenuation, ray&scattered) const {
        vec3 outward_normal;
        vec3 reflected = reflect(r_in.direction(), rec.normal);
        float ni_over_nt;
        attenuation = vec3(1.0, 1.0, 1.0);
        vec3 refracted;
        if (dot(r_in.direction(), rec.normal) > 0) {
            outward_normal = - rec.normal;
            ni_over_nt = ref_idx;
        } else {
            outward_normal = rec.normal;
            ni_over_nt = 1.0 / ref_idx;
        }
        if (refract(r_in.direction(), outward_normal, ni_over_nt, refracted)) {
            scattered = ray(rec.p, refracted);
            return true;
        } else {
            scattered = ray(rec.p, reflected);
        }
        return false;
    }
};


#endif //DIELECTRIC_H
