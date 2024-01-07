#pragma once 
#include "vec3.h"

template <typename T>
class ray {
    private:
        point3<T> orig; 
        vec3<T> dir; 
    public:
        // constructor 
        ray() {}
        ray(point3<T>& origin, vec3<T>& directory):
            orig(origin), dir(directory) {}
        // member functions 
        point3<T> origin() {return orig; }
        vec3<T> direction() {return dir; }
        point3<T> at(double t) {
            return orig + dir*t; 
        }

}; 