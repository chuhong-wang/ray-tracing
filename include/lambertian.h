#pragma once 
#include "material.h"
#include "common.h"

class Lambertian:public Material {
    public:
    Color<double> attenuation;

    Lambertian(Color<double> t_reflectance):attenuation(t_reflectance) {}

    bool scatter(const Ray<double>& ray_in, HitRecord& rec, Color<double>& t_attenuation, Ray<double>& ray_scattered) const override {
        auto unit_normal = unit_vector(rec.normal);
        auto contactSphere_center = rec.P + unit_normal; 
        auto point_on_contactSphere = contactSphere_center + random_vector(contactSphere_center); 
        auto reflection_vec = point_on_contactSphere - rec.P;

        ray_scattered = Ray<double>(rec.P, reflection_vec); 
        t_attenuation = attenuation; 
        return true; 
    } 
}; 