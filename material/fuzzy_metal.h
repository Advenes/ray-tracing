#pragma once
#include "material.h"

class fuzzy_metal : public material {
    public:
    fuzzy_metal(const vec3& albedo, const double fuzziness) : albedo(albedo), fuzziness(fuzziness) {}

    bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const override{
        vec3 reflected = reflect(r_in.direction(), rec.normal);
        vec3 with_distortion = reflected + random_unit_vector() * fuzziness;
        if (with_distortion.near_zero()) {
            with_distortion = rec.normal;
        }
        scattered = ray(rec.p, with_distortion);
        attenuation = albedo;
        return (dot(scattered.direction(), rec.normal) > 0);
    }

private:
    vec3 albedo;
    double fuzziness;
};
