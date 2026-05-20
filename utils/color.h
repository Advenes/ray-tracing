
#pragma once
#include "vec3.h"

#include <iostream>

void write_color(std::ostream& out, const vec3& v) {
    auto r = (int) v.x();
    auto g = (int) v.y();
    auto b = (int) v.z();

    out << r << ' ' << g << ' ' << b << '\n';
}