#pragma once 
#include "interval.h"
#include "vec3.h"
#include "ray.h"

// axis aligned bounding box 
class Aabb {
    private:
    Interval x, y, z; 

    public:
    // constructor 
    Aabb(const Interval& t_x, const Interval& t_y, const Interval& t_z):
        x(t_x), y(t_y), z(t_z) {}
    Aabb(const Point3<double>& diag_endpoint1, const Point3<double>& diag_endpoint2):
        x(diag_endpoint1[0], diag_endpoint2[0]), y(diag_endpoint1[1], diag_endpoint2[1]), z(diag_endpoint1[2], diag_endpoint2[2]) {}
    
    // utility function 
    bool hit(const Ray<double>& ray_in) const {
        auto invD = ray_in.direction(); 
        auto tx0 = (x[0] - ray_in.origin())*invD; 

    }
}; 