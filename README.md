# cpp_raytracer

### About the project
A raytracer written in C++. Outputs a .ppm file. The base of project was made while following the "Raytracing in a Weekend" book by Peter Shirley.

### Screenshots
This screenshot was made after adding multithreading support:

![screenshot_01](https://github.com/tudormacovei/cpp_raytracer/blob/main/screenshots/screen_01.jpg)

### building
For Windows, use Microsoft's C++ compiler. (Do not use MinGW as `std::thread` is not supported).
