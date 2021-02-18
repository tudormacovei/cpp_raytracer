cmake_minimum_required(VERSION 3.16)
project(cpp_raytracer)

set(CMAKE_CXX_STANDARD 14)

add_executable(cpp_raytracer main.cpp hitable.h sphere.h hitable_list.h camera.h postprocess.h material.h lamberitan.h helper_functions.h metal.h dielectric.h)