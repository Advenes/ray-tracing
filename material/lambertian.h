#pragma once
#include "material.h"

class lambertian : public material {
public:
    lambertian(const vec3& albedo) : albedo(albedo) {

    }

    bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered)
    const override {
        auto scatter_direction = rec.normal + random_unit_vector();
        if (scatter_direction.near_zero()) {
            scatter_direction = rec.normal;
        }
        scattered = ray(rec.p, scatter_direction);
        attenuation = albedo;
        return true;
    }


private:
    vec3 albedo;
};