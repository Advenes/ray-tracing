#pragma once
#include "../utils/vec3.h"
#include "../utils/ray.h"

class hit_record {
public:
    vec3 p; // exact point that collides with the object
    vec3 normal; // a normal from that object
    double t; // time param

    // true if hit from the outside, false if hit from the inside
    bool front_face;

    // function bellow sets based on what the dot product between ray and outward normal
    // returns, then sets on that information the normal boolean
    void set_face_normal(const ray& r, const vec3& outward_normal) {
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class hittable {
public:
    virtual ~hittable() = default;

    virtual bool hit (const ray& r, double ray_tmin, double ray_tmax, hit_record& rec) const = 0;


};