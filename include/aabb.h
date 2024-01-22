#pragma once 

#include "interval.h"
#include "vec3.h"
#include "ray.h"

// axis aligned bounding box 
class Aabb {
    private:
    Interval2f x, y, z; 

    public:
    // constructor 
    Aabb();
    Aabb(const Interval2f& t_x, const Interval2f& t_y, const Interval2f& t_z);
    Aabb(const Point3f& diag_endpoint1, const Point3f& diag_endpoint2);     
    
    // utility function 
    Interval2f axis(int i) const; 

    void add(const Aabb& obj_bbox);

    bool hit(const Ray& ray_in, Interval2f ray_t) const;
}; 