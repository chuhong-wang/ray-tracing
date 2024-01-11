#pragma once 
#include "material.h"
#include "common.h"

class Lambertian:public Material {
    public:
    Color<double> attenuation;
    double fuzziness = 0; 

    Lambertian(Color<double> t_reflectance):attenuation(t_reflectance) {}
    Lambertian(Color<double> t_reflectance, double t_fuzz):attenuation(t_reflectance), fuzziness(t_fuzz) {}

    bool scatter(const Ray<double>& ray_in, HitRecord& rec, Color<double>& t_attenuation, Ray<double>& ray_scattered) const override {
        auto unit_normal = unit_vector(rec.normal);
        auto contactSphere_center = rec.P + unit_normal; 
        auto point_on_contactSphere = contactSphere_center + random_vector(contactSphere_center); 
        auto reflection_vec = point_on_contactSphere - rec.P;
        auto random_unit_vec = random_vector(Vec3<double>(0, 0, 0)); 
        auto fuzzed = unit_vector(random_unit_vec)*fuzziness + reflection_vec;

        ray_scattered = Ray<double>(rec.P, fuzzed); 
        t_attenuation = attenuation; 
        return true; 
    } 
}; 