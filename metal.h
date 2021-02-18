//
// Created by tudor on 18/02/2021.
//

#ifndef CPP_RAYTRACER_METAL_H
#define CPP_RAYTRACER_METAL_H

#include "ray.h"
#include "hitable.h"
#include "helper_functions.h"

class metal : public material {
public:
    vec3 albedo;
    float fuzz;

    metal(const vec3 &a, float f) : albedo(a) {if (f < 1) fuzz = f; else fuzz = 1;}

    virtual bool scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const {
        vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
        scattered = ray(rec.p, reflected + fuzz * random_in_unit_sphere());
        attenuation = albedo;
        return (dot(scattered.direction(), rec.normal) > 0);
    }
};


#endif //CPP_RAYTRACER_METAL_H
