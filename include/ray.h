#pragma once 
#include "vec3.h"

template <typename T>
class Ray {
    private:
        Point3<T> orig; 
        Vec3<T> dir; 
    public:
        // constructor 
        Ray() {}
        Ray(Point3<T>& t_origin, Vec3<T>& t_direction):
            orig(t_origin), dir(t_direction) {}
        // member functions 
        Point3<T> origin() const {return orig; }
        Vec3<T> direction() const {return dir; }
        Point3<T> at(double t) {
            return orig + dir*t; 
        }

}; 