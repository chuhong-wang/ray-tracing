#pragma once
#include "ray.h"
#include "hit_record.h"
#include "interval.h"

class hittable{
    public:
    virtual ~hittable() = default; 
    virtual bool hit(ray<double> r_,  interval intv, hit_record& rec_) const = 0; 
}; 