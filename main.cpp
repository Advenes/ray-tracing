#include <iostream>
#include "utils/color.h"
#include "utils/vec3.h"

int main() {

    const int img_width = 256;
    const int img_height = 256;

    std::cout << "P3\n" << img_width << ' ' << img_height << "\n255" <<  '\n';

    for (int i = 1; i <= img_height; i++) {
        for (int j = 1; j <= img_width; j++) {
            std::clog << "\rScanlines remaining: " << i << ' ' << j << '\n' << std::flush;
            double r = (255 + j - img_height);
            double g = (255 + i - img_width);
            double b = (255 + j - img_height);
            write_color(std::cout, {r,g,b});
        }
        std::cout << '\n';
    }
}
