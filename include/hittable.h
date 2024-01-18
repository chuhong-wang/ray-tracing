#pragma once
#include "ray.h"
#include "hit_record.h"
#include "interval.h"
#include "material.h"
#include "aabb.h"

class hittable{
    public:
    virtual ~hittable() = default; 
    virtual bool hit(Ray<double> ray_in,  Interval intv, HitRecord& rec_) const = 0; 
    virtual Aabb bounding_box() const = 0; 
    
    private:
    std::shared_ptr<Material> mat; 


}; 