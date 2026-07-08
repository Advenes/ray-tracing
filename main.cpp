#include <iostream>

#include "hittable/hittable_list.h"
#include "hittable/sphere.h"
#include "utils/common_includes.h"
#include "camera/camera.h"
#include "material/metal.h"
#include "material/lambertian.h"
#include "material/fuzzy_metal.h"
#include "application/application.h"
#include "hittable/bvh.h"

enum class render_type {
    PPM_FILE = 1,
    WINDOW = 2
};

constexpr render_type RENDER_TYPE = render_type::WINDOW;

int IMG_WIDTH = 1024;
double ASPECT_RATIO = 16.0/9.0;
int IMG_HEIGHT = IMG_WIDTH / ASPECT_RATIO;

int main() {

    hittable_list world;

    // add all balls


    auto big_center = vec3(0,-50,-40);
    auto radius = 50;
    world.add(std::make_shared<sphere>(big_center, radius, std::make_shared<lambertian>(vec3{0.1,0.1,0.2})));
    for (int i{0}; i < 100; i++) {
        vec3 dir = random_unit_vector();
        while (dir.y() < 0.90) {
            dir = random_unit_vector();
        }
        auto r = random_double() * 3;
        auto point = big_center + (radius + r) * dir;
        auto color = vec3::random();

        std::shared_ptr<material> material;
        if (i % 2 == 0) material = std::make_shared<metal>(color);
        else {
            material = std::make_shared<lambertian>(color);
            auto point2 = point + random_unit_vector();
            world.add(std::make_shared<sphere>(point, point2, r, material));
        }
    }

    world = hittable_list(make_shared<bvh_node>(world));

    camera camera(&IMG_WIDTH, &IMG_HEIGHT);

    if constexpr (RENDER_TYPE == render_type::PPM_FILE) {
        camera.render(world);
    }
    else {
        application application(&IMG_WIDTH, &IMG_HEIGHT, world, camera);
        application.run();
    }
}
