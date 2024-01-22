#pragma once
#include <cmath>
#include "material.h"
#include "hit_record.h"
#include "common.h"

class Dielectric: public Material {
    private:
        float refractive_idx; 
    public:
        Dielectric(float t_refractive_idx): refractive_idx(t_refractive_idx) {}
        bool scatter(const Ray& ray_in, HitRecord& rec, Color& t_attenuation, Ray& ray_scattered) const {
            t_attenuation = Color(1,1,1);
            auto refractive_idx_ratio = rec.front_face? 1/refractive_idx : refractive_idx; 
            auto ray_in_dir = unit_vector(ray_in.direction()); 
            auto cosine_thetaIn = fmin(dot_product(-ray_in_dir, rec.normal), 1.0); 

            // Schlick Approximation
            auto R0 = (1-refractive_idx_ratio)/(refractive_idx_ratio+1); 
            R0 = R0 * R0; 
            auto R_schlick = R0 + (1-R0)*pow((1-cosine_thetaIn), 5); 

            auto sine_thetaIn = sqrt(1-cosine_thetaIn*cosine_thetaIn); 
            auto sine_thetaOut = refractive_idx_ratio*sine_thetaIn; 

            auto normal_distribution = random_double<float>(); 
            if (sine_thetaOut > 1.0 || R_schlick > normal_distribution) {
                auto reflect_dir = reflect(ray_in_dir, rec.normal); 
                ray_scattered = Ray(rec.P, reflect_dir, ray_in.time());
            }
            else {
                auto refract_dir = refract(ray_in_dir, rec.normal, refractive_idx_ratio); 
                ray_scattered = Ray(rec.P, refract_dir, ray_in.time());
            }
            return true; 
        }

}; 