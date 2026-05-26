#pragma once
#include "../utils/common_includes.h"
#include "../hittable/hittable_list.h"

class camera {
public:
    int img_width = 512;
    double aspect_ratio = 16.0 / 9.0;
    int samples_per_pixel = 10;
    int max_bounces = 10;

    void render(const hittable& world) {

        initialize();
        // ppm format stuff
        std::cout << "P3\n" << img_width << ' ' << img_height << "\n255" <<  '\n';


        for (int i = 0; i < img_height; i++) {
            std::clog << "\rScanlines remaining: " << i << ' ' << img_height << '\n' << std::flush;
            for (int j = 0; j < img_width; j++) {
                vec3 color(0,0,0);
                // we sample randomly around our pixel and make a color out of it
                // to create a basic antialiasing
                for (int sample = 0; sample < samples_per_pixel; sample++) {
                    ray r = get_ray(j, i);
                    color += ray_color(r, max_bounces, world);
                }
                write_color(std::cout, pixel_samples_scale * color);
            }
        }

    }

private:

    int img_height;
    vec3 camera_pos;

    vec3 pixel_delta_ltr;
    vec3 pixel_delta_ttb;
    vec3 first_pixel;

    double pixel_samples_scale;

    void initialize() {

        // dimesions for out final image

        img_height = int(img_width / aspect_ratio);
        img_height = (img_height < 1) ? 1 : img_height;
        // aspect ratio and viewport w and h
        aspect_ratio = double (img_width) / double (img_height);
        double viewport_height = 2.0;
        double viewport_width = aspect_ratio * viewport_height;

        pixel_samples_scale = 1.0 / samples_per_pixel;

        camera_pos = {0,0,0};

        double focal_length = 1.0;
        vec3 vltr = {viewport_width, 0, 0}; // viewport vector from left to right
        vec3 vttb = {0, (double) -viewport_height, 0}; // viewport vector from top to bottom
        vec3 q = camera_pos - vltr / 2 - vttb / 2 - vec3(0,0, focal_length); // top left point of viewport
        pixel_delta_ltr = {viewport_width / img_width, 0, 0}; //
         pixel_delta_ttb = {0, -viewport_height / img_height, 0};
        first_pixel = q + pixel_delta_ltr / 2 + pixel_delta_ttb / 2;

    }

    ray get_ray(int i, int j) const {
        // Construct a camera ray originating from the origin and directed at randomly sampled
        // point around the pixel location i, j.

        auto offset = sample_square();
        auto pixel_sample = first_pixel
                          + ((i + offset.x()) * pixel_delta_ltr)
                          + ((j + offset.y()) * pixel_delta_ttb);

        auto ray_origin = camera_pos;
        auto ray_direction = pixel_sample - ray_origin;

        return ray(ray_origin, ray_direction);
    }

    vec3 sample_square() const {
        // Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit square.
        return vec3(random_double() - 0.5, random_double() - 0.5, 0);
    }

    vec3 ray_color(const ray& r,const int bounces_left, const hittable& world) const {
        if (bounces_left == 0) return {0,0,0};
        hit_record rec; // creating a record if we hit anything on this specific pixel
        if (world.hit(r, interval(0, infinity), rec)) { // if anything is hit
            vec3 direction = random_on_hemisphere(rec.normal);
            return 0.5 * ray_color(ray(rec.p, direction), bounces_left-1, world);
        }

        vec3 unit_direction = unit_vector(r.direction()); // if nothing is hit we simply apply a top-down sky fade
        auto a = 0.5*(unit_direction.y() + 1.0);
        return (1.0-a)*vec3(1.0, 1.0, 1.0) + a*vec3(0.5, 0.7, 1.0);
    }

    void write_color(std::ostream& out, const vec3& v) {

        auto r = v.x();
        auto g = v.y();
        auto b = v.z();

        static const interval intensity(0.000, 0.999);
        int rbyte = int(256 * intensity.clamp(r));
        int gbyte = int(256 * intensity.clamp(g));
        int bbyte = int(256 * intensity.clamp(b));

        out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';

    }
};