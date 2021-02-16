#include <iostream>
#include <fstream>

using namespace std;

int main() {
    int nx;
    int ny;
    ofstream fout("render.ppm");

    nx = 200;
    ny = 100;

    fout << "P3\n" << nx << " " << ny << "\n255\n";
    // rows top to bot
    for (int j = ny - 1; j >= 0; j--) {
        // each row left to right
        for (int i = 0; i < nx; i++) {
            float r = float (i) / float(nx);
            float g = float (j) / float(ny);
            float b = 0.2;
            int ir = int (255.99 * r);
            int ig = int (255.99 * g);
            int ib = int (255.99 * b);
            fout << ir << " " << ig << " " << ib << "\n";
        }
    }
    fout.close();
}