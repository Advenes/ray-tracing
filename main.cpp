#include <iostream>

#include "hittable/hittable_list.h"
#include "hittable/sphere.h"
#include "utils/common_includes.h"
#include "camera/camera.h"

int main() {

    // hittable list "world" object
    hittable_list world;

    world.add(std::make_shared<sphere>(vec3(0,-100.5,-3), 100));
    world.add(std::make_shared<sphere>(vec3(0,0,-1), 0.5));

    camera camera;

    camera.render(world);
}