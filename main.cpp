#include <iostream>
#include <fstream>
#include <cmath>
#include <random>
#include <stdlib.h>

#include "hitable_list.h"
#include "sphere.h"
#include "float.h"
#include "camera.h"

vec3 color(const ray& r, hitable *world) {
    hit_record rec;
    if (world->hit(r, 0.0, FLT_MAX, rec)) {
        return 0.5*vec3(rec.normal.x() + 1, rec.normal.y() + 1, rec.normal.z() + 1);
    } else {
        vec3 unit_direction = unit_vector(r.direction());
        float t = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - t) * vec3(1.0,1.0,1.0) + t* vec3(0.5,0.7,1.0);
    }
}

int main() {
    int nx;
    int ny;
    int ns;
    hitable *list[2];
    std::ofstream render_file("render.ppm");
    camera cam;

    nx = 200;
    ny = 100;
    ns = 100;
    render_file << "P3\n" << nx << " " << ny << "\n255\n";


    list[1] = new sphere(vec3(0,0,-1), 0.5);
    list[0] = new sphere(vec3(0,-100.5,-1), 100);
    hitable_list *world = new hitable_list(list,2);
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
                col += color(r, reinterpret_cast<hitable *>(world));
            }
            col /= float(ns);
            int ir = int(255.99 * col.r());
            int ig = int(255.99 * col.g());
            int ib = int(255.99 * col.b());
            render_file << ir << " " << ig << " " << ib << "\n";
        }
    }
    render_file.close();
}