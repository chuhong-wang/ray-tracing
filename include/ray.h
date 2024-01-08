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
        Ray(Point3<T>& origin, Vec3<T>& directory):
            orig(origin), dir(directory) {}
        // member functions 
        Point3<T> origin() {return orig; }
        Vec3<T> direction() {return dir; }
        Point3<T> at(double t) {
            return orig + dir*t; 
        }

}; 