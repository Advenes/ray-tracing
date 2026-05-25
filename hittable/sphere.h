
#pragma once
#include "hittable.h"
#include "../utils/common_includes.h"

class sphere : public hittable {
    public:
    sphere(const vec3& center, double radius) : center(center), radius(radius) {}

    bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override {
        vec3 oc = center - r.origin(); // vector from ray to center of sphere
        auto a = r.direction().length_squared(); // b * b (square length of direction of radius
        auto half_b = dot(r.direction(), oc); // half b param
        auto c = oc.length_squared() - radius * radius; //  (C-A) * (C-A) - r^2

        auto discriminant = half_b * half_b - a * c;
        if (discriminant < 0) return false; // delta < 0 -> object not hit

        auto sqrtD = sqrt(discriminant);

        // ray can hit the sphere through it, giving us delta > 0 and two roots of equation
        auto root = (half_b - sqrtD) / a;
        if (root <= t_min || t_max <= root) { // this checks if 1st root is in max and min
            root = (half_b + sqrtD) / a;
            if (root <= t_min || t_max <= root) // same for 2nd
                return false; // if both are not inside -> false
        }

        rec.t = root; // time param is set to root
        rec.p = r.at(rec.t); // exact point in 3d where the sphere was hit
        vec3 outward_normal = (rec.p - center) / radius;
        rec.set_face_normal(r, outward_normal); // setting the normal based on how the ray hit our object

        return true;
    }




private:
    vec3 center;
    double radius;
};