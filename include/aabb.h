#pragma once 
#include <cmath>
#include "interval.h"
#include "vec3.h"
#include "ray.h"

// axis aligned bounding box 
class Aabb {
    private:
    Interval x, y, z; 

    public:
    // constructor 
    Aabb():x(0,0), y(0,0), z(0,0) {}
    Aabb(const Interval& t_x, const Interval& t_y, const Interval& t_z):
        x(t_x), y(t_y), z(t_z) {}
    Aabb(const Point3<double>& diag_endpoint1, const Point3<double>& diag_endpoint2):
        x(diag_endpoint1[0], diag_endpoint2[0]), y(diag_endpoint1[1], diag_endpoint2[1]), z(diag_endpoint1[2], diag_endpoint2[2]) {}
    
    // utility function 
    Interval axis(int i) const {
        if(i==0) return x;
        else if (i==1) return y; 
        return z; 
    }

    // merge two bounding boxes 
    void add(const Aabb& obj_bbox) {
        x.combine(obj_bbox.x); 
        y.combine(obj_bbox.y); 
        z.combine(obj_bbox.z); 
    }

    bool hit(const Ray<double>& ray_in) const {
        auto invD = 1.0/ray_in.direction(); 
        for (int i = 0; i<3; ++i){
            auto itvl = axis(i);  
            auto tx0 = (itvl.min - ray_in.origin()[i])*invD[i]; 
            auto tx1 = (itvl.max - ray_in.origin()[i])*invD[i]; 

            if(invD[i]<0.0) {
                auto tmp = tx0; tx0 = tx1; tx1 = tmp; 
            }

            itvl.min = fmax(tx0, itvl.min); 
            itvl.max = fmin(tx1, itvl.max); 

            if(itvl.min >= itvl.max) {return false; }
        }
        return true; 
    }
}; 