
#pragma once
#include "hittable.h"
#include "../utils/common_includes.h"

class sphere : public hittable {
    public:
    sphere(const vec3& center, double radius) : center(center), radius(radius) {}

    bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override {
        vec3 oc = center - r.origin();
        auto a = r.direction().length_squared();
        auto half_b = dot(r.direction(), oc);
        auto c = oc.length_squared() - radius * radius;

        auto discriminant = half_b * half_b - a * c;
        if (discriminant < 0) return false;

        auto sqrtD = sqrt(discriminant);

        auto root = (half_b - sqrtD) / a;
        if (root <= t_min || t_max <= root) {
            root = (half_b + sqrtD) / a;
            if (root <= t_min || t_max <= root)
                return false;
        }

        rec.t = root;
        rec.p = r.at(rec.t);
        vec3 outward_normal = (rec.p - center) / radius;
        rec.set_face_normal(r, outward_normal);

        rec.normal = (rec.p - center) / radius;

        return true;
    }




private:
    vec3 center;
    double radius;
};