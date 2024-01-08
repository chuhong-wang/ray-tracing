#pragma once
#include "ray.h"
#include "hit_record.h"
#include "interval.h"

class hittable{
    public:
    virtual ~hittable() = default; 
    virtual bool hit(Ray<double> r_,  Interval intv, HitRecord& rec_) const = 0; 
}; 