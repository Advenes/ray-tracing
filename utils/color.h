
#pragma once
#include <iostream>
#include "./vec3.h"
#include "./ray.h"
#include "../hittable/hittable.h"
#include "../math/constants.h"

class hittable_list;

inline double hitSphere(ray r, double radius, vec3& center) {
    vec3 oc = r.origin() - center;

    auto a = r.direction().length_squared();
    auto half_b = dot(r.direction(), oc);
    auto c = oc.length_squared() - radius * radius;

    auto discriminant = half_b * half_b - a * c;

    if (discriminant < 0) return -1.0;

    return (-half_b - std::sqrt(discriminant)) / a;
}

inline vec3 ray_color(ray r, const hittable_list& list ) {
    hit_record rec;
    if (list.hit(r, 0, infinity, rec)) {
        return 0.5 * (rec.normal + vec3(1, 1, 1));
    }

    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5*(unit_direction.y() + 1.0);
    return (1.0-a)*vec3(1.0, 1.0, 1.0) + a*vec3(0.5, 0.7, 1.0);
}

void write_color(std::ostream& out, const vec3& v) {
    out << int(v.x() * 255) << ' ' << int(v.y() * 255) << ' ' << int(v.z() * 255) << '\n';
}