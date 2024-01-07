#pragma once
#include "ray.h"
#include "hit_record.h"

class hittable{
    public:
    virtual ~hittable() = default; 
    virtual bool hit(ray<double> r_, double r_min, double r_max, hit_record& res) const = 0; 
}; 