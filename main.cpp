#include <iostream>
#include "utils/color.h"
#include "utils/vec3.h"
#include "utils/ray.h"

int main() {

    const int img_width = 256;
    const int img_height = 256;

    std::cout << "P3\n" << img_width << ' ' << img_height << "\n255" <<  '\n';

    const double aspect_ratio = double (img_width) / double (img_height);
    const double viewport_height = 2.0;
    const double viewport_width = aspect_ratio * viewport_height;

    vec3 camera_pos = {0,0,0};

    double focal_length = 1.0;
    vec3 vltr = {viewport_width, 0, 0};
    vec3 vttb = {0, (double) -viewport_height, 0};
    vec3 q = camera_pos - vltr / 2 - vttb / 2 - vec3(0,0, focal_length);
    vec3 pixel_delta_ltr = {viewport_width / img_width, 0, 0};
    vec3 pixel_delta_ttb = {0, -viewport_height / img_height, 0};
    vec3 first_pixel = q + pixel_delta_ltr / 2 + pixel_delta_ttb / 2;

    double sphere_r = 0.5;
    vec3 sphere_center = camera_pos - vec3{0,0,1};

    for (int i = 0; i < img_height; i++) {
        for (int j = 0; j < img_width; j++) {
            std::clog << "\rScanlines remaining: " << i << ' ' << img_height << '\n' << std::flush;
            vec3 pixel_center = first_pixel + pixel_delta_ltr * j + pixel_delta_ttb * i;
            auto ray_dir = pixel_center - camera_pos;
            ray r(camera_pos, ray_dir);
            auto color = ray_color(r);
            if (hitSphere(r, sphere_r, sphere_center)) {
                write_color(std::cout, color, 1);
                continue;
            }
            write_color(std::cout, color, 0);
        }
    }
}