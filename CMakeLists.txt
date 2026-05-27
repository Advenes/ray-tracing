cmake_minimum_required(VERSION 3.20)
project(raytracer)

set(CMAKE_CXX_STANDARD 20)

add_executable(raytracer main.cpp
        utils/vec3.h
        utils/color.h
        utils/delta.h
        utils/ray.h
        hittable/hittable.h
        hittable/sphere.h
        hittable/hittable_list.h
        math/constants.h
        utils/common_includes.h
        camera/camera.h
        material/material.h
        "material/lambertian.h"
        material/metal.h
        material/fuzzy_metal.h
)
