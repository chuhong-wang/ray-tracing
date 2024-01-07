#pragma once

#include <vector>
#include <memory> 

#include "hittable.h"

using std::shared_ptr; 

class Hittable_list:public hittable {
    private:
    // data member 
    std::vector<std::shared_ptr<hittable>> obj_ptrs; 

    public:
    // constructor
    Hittable_list() = default; 
    Hittable_list(shared_ptr<hittable> obj_ptr) { add(obj_ptr); }

    void add(shared_ptr<hittable> obj_ptr){ 
        obj_ptrs.push_back(obj_ptr); 
    }

    // member function 
    bool hit(ray<double> ray_, double ray_t_min, double ray_t_max, hit_record& rec) const override {
        bool hit_something = false; 
        // scan all the objects and determine the smallest t hittable
        for (auto obj:obj_ptrs){
            if (obj->hit(ray_, ray_t_min, ray_t_max, rec)){
                hit_something = true; 
                ray_t_max = rec.t; 
            }
        }
        return hit_something; 
    }
}; 
