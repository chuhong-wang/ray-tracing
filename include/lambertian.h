#pragma once 
#include "material.h"
#include "common.h"

class Lambertian:public Material {
    public:
    Color attenuation;
    float fuzziness = 0; 

    Lambertian(Color t_reflectance):attenuation(t_reflectance) {}

    bool scatter(const Ray& ray_in, HitRecord& rec, Color& t_attenuation, Ray& ray_scattered) const override {
        auto unit_normal = unit_vector(rec.normal);
        auto contactSphere_center = rec.P + unit_normal; 
        auto point_on_contactSphere = contactSphere_center + random_vector(contactSphere_center); 
        auto reflection_vec = point_on_contactSphere - rec.P; 
        ray_scattered = Ray(rec.P, reflection_vec, ray_in.time()); 
        t_attenuation = attenuation; 
        return true; 
    } 
}; 