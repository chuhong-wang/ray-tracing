#pragma once 
#include "material.h"
#include "ray.h"
#include "color.h"
#include "common.h"

class Metal:public Material {
    public: 
    // constructor 
    Metal(Color<double> t_attenuation):attenuation(t_attenuation){}
    Metal(Color<double> t_attenuation, double t_fuzz):attenuation(t_attenuation), fuzziness(t_fuzz<1?t_fuzz:1) {}

    // member function
    bool scatter(const Ray<double>& ray_in, HitRecord& rec, 
        Color<double>& t_attenuation, Ray<double>& ray_scattered ) const override { 
            auto vec_scattered = reflect(ray_in.direction(), rec.normal); 
            ray_scattered = Ray<double>(rec.P, vec_scattered); 
            if(fuzziness>0.0){
                auto random_unit_vec = random_vector(Vec3<double>(0, 0, 0)); 
                auto fuzzed = unit_vector(random_unit_vec)*fuzziness + vec_scattered;
                ray_scattered = Ray<double>(rec.P, fuzzed); 
            }
            t_attenuation = attenuation; 
            return true; 
    }
    
    private:
    Color<double> attenuation; 
    double fuzziness = 0; 

}; 