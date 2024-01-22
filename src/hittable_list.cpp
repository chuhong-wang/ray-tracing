#include "hittable_list.h"

using std::shared_ptr; 


Hittable_list::Hittable_list(shared_ptr<hittable> obj_ptr) { add(obj_ptr); }

void Hittable_list::add(shared_ptr<hittable> obj_ptr){ 
    obj_ptrs.push_back(obj_ptr); 
}

// member function 
bool Hittable_list::hit(Ray ray_, Interval2f intv, HitRecord& rec) const {
    bool hit_something = false; 
    // scan all the objects and determine the smallest t hittable
    for (auto obj:obj_ptrs){
        if (obj->hit(ray_, intv, rec)){
            hit_something = true; 
            intv.update_max(rec.t); 
        }
    }
    return hit_something; 
}

size_t Hittable_list::size() const {
    return obj_ptrs.size(); }

std::vector<std::shared_ptr<hittable>> Hittable_list::get_objects() const {
    return obj_ptrs; 
}

Aabb Hittable_list::bounding_box() const {
    Aabb bbox; 
    for (auto obj_ptr:obj_ptrs){
        bbox.add(obj_ptr->bounding_box()); 
    }
    return bbox; 
}