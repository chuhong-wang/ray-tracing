#pragma once
#include "vec3.h"
#include "ray.h"

class hit_record {
    public:
        double t; // root of quandratic formula
        point3<double> P; // ray.at(t)
        vec3<double> normal;
        bool front_face;

        void set_face_normal(ray<double>& r_, const vec3<double>& outward_normal){
            front_face = (dot_product(r_.direction(), outward_normal)<=0.0); 
            normal = front_face?outward_normal:-outward_normal; 
        }
};