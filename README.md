# cpp_raytracer

### About the project
A raytracer written in C++ that outputs a .ppm file. I've always been interested in how render engines work, so this project is made for learning purposes and not for any practical application. The project is based on the raytracing book series by Peter Shirley. ("Ray Tracing in one Weekend", "Ray Tracing: The Next Week", "Ray Tracing: The Rest of Your Life".)

### Screenshots
This screenshot was made after adding multithreading support:

![screenshot_01](https://github.com/tudormacovei/cpp_raytracer/blob/main/screenshots/screen_01.jpg)

### Building
I am building this on Windows 10 using Microsoft's C++ compiler. (Do not use MinGW as `std::thread` is not supported).
