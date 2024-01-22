#include "aabb.h"
#include <cmath>
// constructor 
Aabb::Aabb(): x(0,0), y(0,0), z(0,0) {}

Aabb::Aabb(const Interval2f& t_x, const Interval2f& t_y, const Interval2f& t_z):
    x(t_x), y(t_y), z(t_z) {}

Aabb::Aabb(const Point3f& diag_endpoint1, const Point3f& diag_endpoint2):
    x(diag_endpoint1[0], diag_endpoint2[0]), y(diag_endpoint1[1], diag_endpoint2[1]), z(diag_endpoint1[2], diag_endpoint2[2]) {}

// utility function 
Interval2f Aabb::axis(int i) const {
    if(i==0) return x;
    else if (i==1) return y; 
    return z; 
}

void Aabb::add(const Aabb& obj_bbox) {
    // merge two bounding boxes 
    x.combine(obj_bbox.x); 
    y.combine(obj_bbox.y); 
    z.combine(obj_bbox.z); 
}

bool Aabb::hit(const Ray& ray_in, Interval2f ray_t) const {
    auto invD = 1.0f/ray_in.direction(); 
    for (int i = 0; i<3; ++i){
        auto itvl = axis(i);  
        auto tx0 = (itvl.min - ray_in.origin()[i])*invD[i]; 
        auto tx1 = (itvl.max - ray_in.origin()[i])*invD[i]; 

        if(invD[i]<0.0) {
            auto tmp = tx0; tx0 = tx1; tx1 = tmp; 
        }

        ray_t.min = fmax(tx0, ray_t.min); 
        ray_t.max = fmin(tx1, ray_t.max); 
        if(itvl.min >= itvl.max) {return false; }
    }
    return true; 
}

