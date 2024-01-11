#pragma once
#include "ray.h"
#include "color.h"

class HitRecord; 

class Material {
    /**
     * a function shared by all materials 
     * given a in-coming ray, update the hit_record and return a scattered ray 
    */
    public: 
    virtual ~Material() = default; 
    virtual bool scatter(const Ray<double>& ray_in, HitRecord& rec, Color<double>& t_attenuation, Ray<double>& ray_scattered) const = 0; 
}; 