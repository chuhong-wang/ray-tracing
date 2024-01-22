#pragma once 
#include "hittable.h"
#include "hittable_list.h"
#include "common.h"


// lambda func for sorting 
bool comparator(std::shared_ptr<hittable> ptr1, std::shared_ptr<hittable> ptr2);

class Bvh_node: public hittable {
    public:
        // constructor 
        Bvh_node(const Hittable_list& obj_list);
        Bvh_node(const std::vector<std::shared_ptr<hittable>>& obj_ptrs, int start, int end);

        bool hit(Ray ray_in,  Interval2f intv, HitRecord& rec_) const override ;
        Aabb bounding_box() const override;

    private: 
        std::shared_ptr<hittable> left; 
        std::shared_ptr<hittable> right; 
        Aabb bbox;  
}; 