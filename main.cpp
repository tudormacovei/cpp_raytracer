#include <iostream>
#include <fstream>
#include <cmath>

#include "vec3.h"
#include "ray.h"


float hit_sphere(const vec3& center, float radius, const ray& r) {
    vec3 oc = r.origin() - center;
    // quadratic eq. from the vectors of the center of the sphere, the radius, and the vectors
    // that define the ray, the discriminant is a parameter t such ray(t) is a point on the sphere
    float a = dot(r.direction(), r.direction());
    float b = 2.0 * dot(oc, r.direction());
    float c = dot(oc, oc) - radius * radius;
    float discriminant = b * b - 4 * a * c;
    if (discriminant < 0) {
        return -1.0;
    } else {
        return ((-b - sqrt(discriminant)) / (2.0 * a));
    }
}

vec3 color(const ray &r) {
    float t = hit_sphere(vec3(0,0,-2), 1, r);
    if (t > 0.0) {
        vec3 N = unit_vector((r.point_at_parameter(t)) - vec3(0, 0, -2)); //normal
        return 0.5 * vec3(N.x() + 1, N.y() + 1, N.z() + 1);
    }
    vec3 unit_direction = unit_vector(r.direction());
    t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) *vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
}

int main() {
    int nx;
    int ny;
    std::ofstream fout("render.ppm");

    nx = 200;
    ny = 100;

    fout << "P3\n" << nx << " " << ny << "\n255\n";

    vec3 lower_left_corner(-2.0, -1.0, -1.0);
    vec3 horizontal(4.0, 0.0, 0.0);
    vec3 vertical(0.0, 2.0, 0.0);
    vec3 origin(0.0, 0.0, 0.0);
    // rows top to bot
    for (int j = ny - 1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            float u = float(i) / float(nx);
            float v = float(j) / float(ny);
            ray r(origin, lower_left_corner + u * horizontal + v * vertical);
            vec3 col = color(r);
            int ir = int(255.99 * col.r());
            int ig = int(255.99 * col.g());
            int ib = int(255.99 * col.b());
            fout << ir << " " << ig << " " << ib << "\n";
        }
    }
    fout.close();
}