#pragma once
#include "ray.h"
#include "hit_record.h"

class hittable{
    public:
    virtual ~hittable() = default; 
    virtual bool hit(ray<double> r_, double r_min_, double r_max_, hit_record& rec_) const = 0; 
}; 