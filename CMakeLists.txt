cmake_minimum_required(VERSION 3.20)
project(raytracer)

set(CMAKE_CXX_STANDARD 20)

add_executable(raytracer main.cpp
        utils/vec3.h
        utils/color.h
        utils/delta.h
        utils/ray.h
    )
