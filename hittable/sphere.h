
#pragma once
#include "hittable.h"
#include "../utils/vec3.h"
#include "../utils/common_includes.h"
#include "../math/interval.h"
#include "../boundings/aabb.h"

class sphere : public hittable {
    public:
    // static sphere
    sphere(const vec3& static_center, double radius, shared_ptr<material> mat) : center(static_center, vec3(0,0,0)), radius(radius), mat(std::move(mat)) {
        auto rvec = vec3(radius, radius, radius);
        bbox = aabb(static_center - rvec, static_center + rvec);
    }
    // moving sphere
    sphere(const vec3& center1, const vec3& center2, double radius, shared_ptr<material> mat)
    : center(center1, center2 - center1), radius(radius), mat(std::move(mat)) {
        vec3 rvec(radius, radius, radius);
        aabb first_box(center.at(0) - rvec, center.at(0) + rvec);
        aabb second_box(center.at(1) - rvec, center.at(1) + rvec);
        bbox = aabb(first_box, second_box);
        // bbox = aabb(center1 - rvec, center2 + rvec);
    }

    bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
        vec3 current_center = center.at(r.time());
        vec3 oc = current_center - r.origin(); // vector from ray to center of sphere
        auto a = r.direction().length_squared(); // b * b (square length of direction of radius
        auto half_b = dot(r.direction(), oc); // half b param
        auto c = oc.length_squared() - radius * radius; //  (C-A) * (C-A) - r^2

        auto discriminant = half_b * half_b - a * c;
        if (discriminant < 0) return false; // delta < 0 -> object not hit

        auto sqrtD = sqrt(discriminant);

        // ray can hit the sphere through it, giving us delta > 0 and two roots of equation
        auto root = (half_b - sqrtD) / a;
        if (!ray_t.surrounds(root)) { // this checks if 1st root is in max and min
            root = (half_b + sqrtD) / a;
            if (!ray_t.surrounds(root)) // same for 2nd
                return false; // if both are not inside -> false
        }

        rec.t = root; // time param is set to root
        rec.p = r.at(rec.t); // exact point in 3d where the sphere was hit
        rec.mat = mat; // material of sphere
        vec3 outward_normal = (rec.p - current_center) / radius;
        rec.set_face_normal(r, outward_normal); // setting the normal based on how the ray hit our object

        return true;
    }

    aabb bounding_box() const override {return bbox;};


private:
    ray center;
    double radius;
    shared_ptr<material> mat;
    aabb bbox;
};
