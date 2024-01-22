#pragma once 
#include "vec3.h"

class Ray {
    private:
        Point3f orig; 
        Vector3f dir; 
        float ray_time; 
    public:
        // constructor 
        Ray(); 
        Ray(const Point3f& t_origin, const Point3f& t_direction, const float t_time);
        
        // member functions 
        Point3f origin() const;
        Vector3f direction() const; 
        float time() const; 
        Vector3f at(float t); 

}; 