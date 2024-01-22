#pragma once
#include <cmath>
#include "material.h"
#include "hit_record.h"
#include "common.h"

class Dielectric: public Material {
    private:
        float refractive_idx; 
    public:
        Dielectric(float t_refractive_idx);
        bool scatter(const Ray& ray_in, HitRecord& rec, Color& t_attenuation, Ray& ray_scattered) const; 

}; 