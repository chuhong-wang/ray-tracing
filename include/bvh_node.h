#pragma once 
#include "hittable.h"
#include "hittable_list.h"
#include "common.h"
#include <algorithm>

// lambda func for sorting 
bool comparator(std::shared_ptr<hittable> ptr1, std::shared_ptr<hittable> ptr2){
    auto comparator_toggle = random_double(0,3); 
    if (comparator_toggle<1) {
        return ptr1->bounding_box().axis(0).min < ptr2->bounding_box().axis(0).min; 
    }
    else if (comparator_toggle<2){
        return ptr1->bounding_box().axis(1).min < ptr2->bounding_box().axis(1).min; 
    }
    else {
        return ptr1->bounding_box().axis(2).min < ptr2->bounding_box().axis(2).min; 
    }
}

class Bvh_node: public hittable {
    public:
        // constructor 
        Bvh_node(const Hittable_list& obj_list): Bvh_node(obj_list.get_objects(), 0, obj_list.size()) {}
        Bvh_node(const std::vector<std::shared_ptr<hittable>>& obj_ptrs, int start, int end) {
            auto objects = obj_ptrs; 

            if (end-start==1) {
                left = objects[start]; 
                right = objects[start];
            }
            else if (end - start == 2){
                left = objects[start]; 
                right = objects[start + 1]; 
            }
            else {
                std::sort(objects.begin()+start, objects.begin()+end,  comparator); 
                std::size_t const half_size = (end-start) / 2; 
                left = std::make_shared<Bvh_node>(objects, start, start+half_size); 
                right = std::make_shared<Bvh_node>(objects, start+half_size, end); 
            }
            bbox = Aabb(left->bounding_box()); 
            bbox.add(right->bounding_box());
        }

        bool hit(Ray<double> ray_in,  Interval intv, HitRecord& rec_) const override {
            if(bbox.hit(ray_in, intv)){
                bool left_hit = left->hit(ray_in, intv, rec_);
                if(left_hit) {intv.update_max(rec_.t); }
                bool right_hit = right->hit(ray_in, intv, rec_);
                return left_hit||right_hit; 
            }
            else {return false; }
        }
        Aabb bounding_box() const override { return bbox; }

    private: 
        shared_ptr<hittable> left; 
        shared_ptr<hittable> right; 
        Aabb bbox;  
}; 