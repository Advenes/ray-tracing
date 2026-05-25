
#pragma once
#include "vec3.h"
#include "ray.h"
#include <iostream>
#include "delta.h"

bool hitSphere(ray r, double radius, vec3& center) {
    vec3 oc = center - r.origin();
    auto a = dot(r.direction(), r.direction());
    auto b = -2.0 * dot(r.direction(), oc);
    auto c = dot(oc, oc) - radius * radius;

    if (!delta<double>(a,b,c).empty()) return true;

    return false;
}

vec3 ray_color(ray r) {
    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5 *  (unit_direction.y() + 1.0);
    return (1.0 - a) * vec3(0.9, 0.9, 0.9) + a * vec3(0.6, 0.65, 0.9    );
}

void write_color(std::ostream& out, const vec3& v, const int type) {
    if (type == 1) {
        out << 255 << ' ' << 0 << ' ' << 0 << '\n';
        return;
    }
    out << int(v.x() * 255) << ' ' << int(v.y() * 255) << ' ' << int(v.z() * 255) << '\n';
}