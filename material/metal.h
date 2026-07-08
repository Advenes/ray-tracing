#pragma once
#include "material.h"

class metal : public material {
public:
    metal(const vec3& albedo) : albedo(albedo) {};

    bool scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const override {
        vec3 reflected = reflect(r_in.direction(), rec.normal);
        scattered = ray(rec.p, reflected, r_in.time());
        attenuation = albedo;
        return true;
    }

private:
    vec3 albedo;
};