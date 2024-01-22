#pragma once

#include <vector>
#include <memory>

#include "hittable.h"


class Hittable_list:public hittable {
    private:
    // data member 
    std::vector<std::shared_ptr<hittable>> obj_ptrs;  

    public:
    // constructor
    Hittable_list() = default; 
    Hittable_list(std::shared_ptr<hittable> obj_ptr);

    void add(std::shared_ptr<hittable> obj_ptr); 

    // member function 
    bool hit(Ray ray_, Interval2f intv, HitRecord& rec) const override; 

    size_t size() const; 

    std::vector<std::shared_ptr<hittable>> get_objects() const ; 
    
    Aabb bounding_box() const override; 
}; 
