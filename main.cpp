#include <iostream>

#include "hittable/hittable_list.h"
#include "hittable/sphere.h"
#include "utils/common_includes.h"
#include "camera/camera.h"
#include "material/metal.h"
#include "material/lambertian.h"
#include "material/fuzzy_metal.h"
#include "application/application.h"

enum class render_type {
    PPM_FILE = 1,
    WINDOW = 2
};

constexpr render_type RENDER_TYPE = render_type::WINDOW;

constexpr int IMG_WIDTH = 256;
constexpr double ASPECT_RATIO = 16.0/9.0;

int main() {

    hittable_list world;

    // add all balls
    world.add(std::make_shared<sphere>(vec3(0,-100.5,-3), 100, std::make_shared<lambertian>(vec3{0.3,0.3,0.3})));
    world.add(std::make_shared<sphere>(vec3(-0.15,0,-1), 0.5, std::make_shared<metal>(vec3{1.0,0.4,0.2})));
    world.add(std::make_shared<sphere>(vec3(3,2.0,-3.5), 1.5, std::make_shared<metal>(vec3{0.3,1.0,0.3})));
    world.add(std::make_shared<sphere>(vec3(-1.5,0,-1), 0.5, std::make_shared<lambertian>(vec3{0.1,0.4,0.9})));
    world.add(std::make_shared<sphere>(vec3(0.9,-0.1,-0.9), 0.4, std::make_shared<fuzzy_metal>(vec3{1.0,1.0,0.1}, 0.25)));

    camera camera(IMG_WIDTH, ASPECT_RATIO);

    if (RENDER_TYPE == render_type::PPM_FILE) {
        camera.render(world);
    }
    else if (RENDER_TYPE == render_type::WINDOW) {
        application application(IMG_WIDTH, world, camera);
        application.run();
    }
}
