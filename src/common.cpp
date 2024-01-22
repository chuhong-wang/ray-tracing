#include "common.h"
#include <cmath>
#include <cstdlib>


Vector random_vector(const Point3& t_orig) {
    // generate a point randomly sampled from a unit radius sphere centered at t_orig
    while (true){ 
        // rejection algorithm: randomly sample the cube, 
        // not return until the vector falls within the sphere 
        float x = random_double(t_orig.x()-1.0f, t_orig.x()+1.0f); 
        float y = random_double(t_orig.y()-1.0f, t_orig.y()+1.0f); 
        float z = random_double(t_orig.z()-1.0f, t_orig.z()+1.0f); 
        Vector v(x,y,z);
        v = v - t_orig;  
        if (v.length() <=1.0f) {
            return v; 
            }
    }
}

Vector random_vector_within_unit_disk() {
    while (true){
        auto p = Vector(random_double(-1.0, 1.0), random_double(-1.0, 1.0), 0); 
        if (p.length()<=1.0f){
            return p; 
        }
    }
}