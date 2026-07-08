#pragma once
#include "../hittable/hittable.h"
#include "boundings/aabb.h"

class material {
public:

    virtual ~material() {}

    virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const {
        return false;
    }
};
