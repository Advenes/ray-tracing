#pragma once
#include "hittable.h"
#include <vector>
#include <memory>
#include "../boundings/aabb.h"

class hittable_list : public hittable {
public:
    std::vector<std::shared_ptr<hittable>> objects; // list of all hittable objects

    hittable_list() {}
    hittable_list(std::shared_ptr<hittable> object) {
        add(object);
    }

    void clear() { objects.clear(); }

    void add(std::shared_ptr<hittable> object) {
        objects.push_back(std::move(object));
        bbox = aabb(bbox, objects.back()->bounding_box());
    }

    bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
        hit_record temp_rec; // temporary hit record where we store information if we have hit anything
        bool hit_anything = false;
        auto closest_so_far = ray_t.max;

        for (const auto& object : objects) {
            if (object->hit(r, interval(ray_t.min, closest_so_far), temp_rec)) { // checking if any of the hittable inside array are hit
                hit_anything = true;
                closest_so_far = temp_rec.t;
                rec = temp_rec; // setting the real hit record to the "returned" temp hit record
            }
        }
        // the one thats closest to the camera has already changed the rec, so we only return true or false
        return hit_anything;
    }

    aabb bounding_box() const override {
        return bbox;
    }


private:
    aabb bbox;
};