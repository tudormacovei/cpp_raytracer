//
// Created by tudor on 18/02/2021.
//

#ifndef METAL_H
#define METAL_H

#include "ray.h"
#include "hitable.h"
#include "helper_functions.h"

class metal : public material {
public:
    texture *albedo;
    float fuzz;

    metal(texture *a, float f) : albedo(a) { if (f < 1) fuzz = f; else fuzz = 1; }

    virtual bool scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const {
        vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
        scattered = ray(rec.p, reflected + fuzz * random_in_unit_sphere());
        attenuation = albedo->value(0, 0, rec.p);
        return (dot(scattered.direction(), rec.normal) > 0);
    }
};

#endif //METAL_H
