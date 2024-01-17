#pragma once 
#include "vec3.h"

template <typename T>
class Ray {
    private:
        Point3<T> orig; 
        Vec3<T> dir; 
        T ray_time; 
    public:
        // constructor 
        Ray() {}
        Ray(Point3<T>& t_origin, Vec3<T>& t_direction, T t_time):
            orig(t_origin), dir(t_direction), ray_time(t_time) {}
        
        // member functions 
        Point3<T> origin() const {return this->orig; }
        Vec3<T> direction() const {return this->dir; }
        T time() const {return this->ray_time; }
        Point3<T> at(double t) {
            return orig + dir*t; 
        }

}; 