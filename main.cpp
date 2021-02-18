#include <iostream>
#include <fstream>
#include <cmath>
#include <random>
#include <cstdlib>
#include <cfloat>

#include "hitable_list.h"
#include "sphere.h"
#include "camera.h"
#include "postprocess.h"
#include "helper_functions.h"
#include "lamberitan.h"
#include "metal.h"
#include "dielectric.h"

// TODO: variable max depth for type of materials?
vec3 color(const ray &r, hitable *world, short depth) {
    hit_record rec;
    if (world->hit(r, 0.001, FLT_MAX, rec)) {    //FLT_MAX
        ray scattered;
        vec3 attenuation;
        if (depth < 12 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
            return attenuation * color(scattered, world, depth + 1);
        } else {
            return vec3(0, 0, 0);
        }
    } else {
        vec3 unit_direction = unit_vector(r.direction());
        float t = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
    }
}

int main() {
    int nx;
    int ny;
    int ns;
    hitable *list[6];
    std::ofstream render_file("render.ppm");
    camera cam;

    nx = 800;
    ny = 400;
    ns = 8;
    render_file << "P3\n" << nx << " " << ny << "\n255\n";

    list[0] = new sphere(vec3(0, -100.5, -1), 100, new lambertian(vec3(0.3, 0.5, 1.0)));
    list[1] = new sphere(vec3(-0.5, 0, -1), 0.5, new lambertian(vec3(0.8, 0.3, 0.3)));
    list[2] = new sphere(vec3(-1.5, 0, -0.8), 0.25, new lambertian(vec3(0.3, 0.6, 1.0)));
    list[3] = new sphere(vec3(0.5, 0.4, -0.7), 0.6, new metal(vec3(1.0, 0.2, 0.1), 0.15));
    list[4] = new sphere(vec3(0, -0.3, -1.3), 0.2, new dielectric(1.31));
    list[5] = new sphere(vec3(-0.1, 0.55, -1.25), 0.2, new dielectric(1.51));
    auto *world = new hitable_list(list, 6);
    // rows top to bot
    for (int j = ny - 1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            vec3 col(0, 0, 0);
            for (int s = 0; s < ns; s++) {
                // random float in [0.0,1.0]
                float r_float = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX));
                float u = float(i + r_float) / float(nx);
                r_float = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX));
                float v = float(j + r_float) / float(ny);

                ray r = cam.get_ray(u, v);
//                vec3 p = r.point_at_parameter(2.0);
                col += color(r, reinterpret_cast<hitable *>(world), 0);
            }
            col /= float(ns);
            postprocess::gamma(col, 2.5);
            int ir = int(255.99 * col.r());
            int ig = int(255.99 * col.g());
            int ib = int(255.99 * col.b());
            render_file << ir << " " << ig << " " << ib << "\n";
        }
    }
    render_file.close();
}