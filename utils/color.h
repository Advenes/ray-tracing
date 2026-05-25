
#pragma once
#include <iostream>
#include "./vec3.h"
#include "./ray.h"
#include "../hittable/hittable.h"
#include "../math/constants.h"

class hittable_list;

inline vec3 ray_color(ray r, const hittable_list& list ) {
    hit_record rec; // creating a record if we hit anything on this specific pixel
    if (list.hit(r, 0, infinity, rec)) { // if anything is hit
        return 0.5 * (rec.normal + vec3(1, 1, 1));
    }

    vec3 unit_direction = unit_vector(r.direction()); // if nothing is hit we simply apply a top-down sky fade
    auto a = 0.5*(unit_direction.y() + 1.0);
    return (1.0-a)*vec3(1.0, 1.0, 1.0) + a*vec3(0.5, 0.7, 1.0);
}

inline void write_color(std::ostream& out, const vec3& v) {
    out << int(v.x() * 255) << ' ' << int(v.y() * 255) << ' ' << int(v.z() * 255) << '\n';
}