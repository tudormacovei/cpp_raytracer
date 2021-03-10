#include <iostream>
#include <fstream>
#include <cmath>
#include <random>
#include <cfloat>
#include <thread>

#include "hitable_list.h"
#include "sphere.h"
#include "camera.h"
#include "postprocess.h"
#include "lamberitan.h"
#include "metal.h"
#include "dielectric.h"

vec3 color(const ray &r, hitable *world, short depth) {
    hit_record rec;
    if (world->hit(r, 0.001, FLT_MAX, rec)) {    //FLT_MAX
        ray scattered;
        vec3 attenuation;

        if (depth < 8 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
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

void render_row(hitable *world, camera &cam, std::vector<vec3> &rgb_out, int nx, int ny, int j) {
    int ns = 512;
    for (int i = 0; i < nx; i++) {
        vec3 col(0, 0, 0);
        for (int s = 0; s < ns; s++) {
            // random float in [0.0,1.0]
            float r_float = random();
            float u = float(i + r_float) / float(nx);
            float v = float(j + r_float) / float(ny);
            ray r = cam.get_ray(u, v);
            col += color(r, world, 0);
        }
        col /= float(ns);
        postprocess::gamma(col, 2.2);

        int ir = int(255.99 * col.r());
        int ig = int(255.99 * col.g());
        int ib = int(255.99 * col.b());
        rgb_out[nx * j + i].set_x(ir);
        rgb_out[nx * j + i].set_y(ig);
        rgb_out[nx * j + i].set_z(ib);
    }
}

inline void out_row(std::vector<vec3> &rgb_out, std::ofstream &render_file, int nx, int j) {
    for (int i = 0; i < nx; i++) {
        render_file << rgb_out[nx * j + i].x() << ' ' << rgb_out[nx * j + i].y() << ' ' << rgb_out[nx * j + i].z()
                    << '\n';
    }
}

int main() {
    int nx = 1000;
    int ny = 500;
    std::vector<vec3> rgb_out;
    hitable *list[6];
    std::ofstream render_file("render.ppm");
    camera cam(vec3(0, 0.5, -4), vec3(-0.3, 0, 0), vec3(0, 1, 0),
               35, float(nx) / float(ny));

    rgb_out.reserve(nx * ny);
    render_file << "P3\n" << nx << " " << ny << "\n255\n";
    list[0] = new sphere(vec3(0, -100.5, -1), 100, new lambertian(new constant_texture(vec3(0.3, 0.5, 1.0))));
    list[1] = new sphere(vec3(-0.5, 0, -1), 0.5, new lambertian(new constant_texture(vec3(0.8, 0.3, 0.3))));
    list[2] = new sphere(vec3(-1.5, 0, -0.8), 0.25, new lambertian(new constant_texture(vec3(0.3, 0.6, 1.0))));
    list[3] = new sphere(vec3(0.5, 0.4, -0.7), 0.6, new metal(new constant_texture(vec3(1.0, 0.2, 0.1)), 0.15));
    list[4] = new sphere(vec3(0, -0.3, -1.3), 0.2, new dielectric(1.31));
    list[5] = new sphere(vec3(-0.1, 0.55, -1.25), 0.2, new dielectric(1.51));
    auto *world = new hitable_list(list, 6);
    hitable *hitable_world = reinterpret_cast<hitable *>(world);
    // rows rendered top to bot
    // naive implementation of multithreading
    // TODO: add variable to control no# of threads
    // TODO: add scheduling to the multithreading implementation
    int j = ny - 1;
    while (j >= 6) {
        std::thread t1(render_row, std::ref(hitable_world), std::ref(cam), std::ref(rgb_out), nx, ny, j);
        std::thread t2(render_row, std::ref(hitable_world), std::ref(cam), std::ref(rgb_out), nx, ny, j - 1);
        std::thread t3(render_row, std::ref(hitable_world), std::ref(cam), std::ref(rgb_out), nx, ny, j - 2);
        std::thread t4(render_row, std::ref(hitable_world), std::ref(cam), std::ref(rgb_out), nx, ny, j - 3);
        std::thread t5(render_row, std::ref(hitable_world), std::ref(cam), std::ref(rgb_out), nx, ny, j - 4);
        std::thread t6(render_row, std::ref(hitable_world), std::ref(cam), std::ref(rgb_out), nx, ny, j - 5);
        t1.join();
        t2.join();
        t3.join();
        t4.join();
        t5.join();
        t6.join();
        out_row(rgb_out, render_file, nx, j);
        out_row(rgb_out, render_file, nx, j - 1);
        out_row(rgb_out, render_file, nx, j - 2);
        out_row(rgb_out, render_file, nx, j - 3);
        out_row(rgb_out, render_file, nx, j - 4);
        out_row(rgb_out, render_file, nx, j - 5);
        j -= 6;
    }
    while (j >= 0) {
        std::thread t1(render_row, std::ref(hitable_world), std::ref(cam), std::ref(rgb_out), nx, ny, j);
        t1.join();
        out_row(rgb_out, render_file, nx, j);
        j--;
    }
    render_file.close();
}