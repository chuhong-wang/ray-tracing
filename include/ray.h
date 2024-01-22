#pragma once 
#include "vec3.h"

class Ray {
    private:
        Point3f orig; 
        Vector3f dir; 
        float ray_time; 
    public:
        // constructor 
        Ray() {}
        Ray(const Point3f& t_origin, const Point3f& t_direction, const float t_time):
            orig(t_origin), dir(t_direction), ray_time(t_time) {}
        
        // member functions 
        Point3f origin() const {return this->orig; }
        Vector3f direction() const {return this->dir; }
        float time() const {return this->ray_time; }
        Vector3f at(float t) {
            return orig + dir*t; 
        }

}; 