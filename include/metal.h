#pragma once 
#include "material.h"
#include "ray.h"
#include "color.h"
#include "common.h"

class Metal:public Material {
    public: 
    // constructor 
    Metal(Color<double> t_attenuation):attenuation(t_attenuation) {}

    // member function
    bool scatter(const Ray<double>& ray_in, HitRecord& rec, 
        Color<double>& t_attenuation, Ray<double>& ray_scattered ) const override {
            auto b = dot_product(ray_in.direction(), rec.normal); 
            auto vec_scattered = ray_in.direction() - 2*b*rec.normal; 
            ray_scattered = Ray<double>(rec.P, vec_scattered); 

            t_attenuation = attenuation; 
            return true; 
    }
    
    Color<double> attenuation; 

}; 