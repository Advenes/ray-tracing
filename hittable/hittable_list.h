#pragma once
#include "hittable.h"
#include <vector>
#include <memory>

class hittable_list : public hittable {
public:
    std::vector<std::shared_ptr<hittable>> objects; // list of all hittable objects

    hittable_list() {}
    hittable_list(std::shared_ptr<hittable> object) {
        add(object);
    }

    void clear() { objects.clear(); }

    void add(std::shared_ptr<hittable> object) {
        objects.push_back(object);
    }

    bool hit(const ray& r, double ray_tmin, double ray_tmax, hit_record& rec) const override {
        hit_record temp_rec; // temporary hit record where we store information if we have hit anything
        bool hit_anything = false;
        auto closest_so_far = ray_tmax;

        for (const auto& object : objects) {
            if (object->hit(r, ray_tmin, closest_so_far, temp_rec)) { // checking if any of the hittable inside array are hit
                hit_anything = true;
                closest_so_far = temp_rec.t;
                rec = temp_rec; // setting the real hit record to the "returned" temp hit record
            }
        }
        // the one thats closest to the camera has already changed the rec, so we only return true or false
        return hit_anything;
    }
};