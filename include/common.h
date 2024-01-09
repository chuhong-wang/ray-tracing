#pragma once
#include <cmath>
#include <cstdlib>
#include "vec3.h"

const double infinity = std::numeric_limits<double>::infinity();
const double PI = 3.1415926535897932385;
const double zeroTolerence = 1e-5; // to treat shadow acne of matte object

template <typename T>
T degree_to_radian(T& degree_){
    return degree_/180.0*PI; 
}

template <typename T>
inline T random_double() {
    return static_cast<T>(rand()/(RAND_MAX + 1.0)); 
}
template <typename T>
inline T random_double(T t_min, T t_max) {
    return t_min + (t_max - t_min)*random_double<T>(); 
}

Vec3<double> random_vector(const Point3<double>& t_orig) {
    // generate a point randomly sampled from a unit radius sphere centered at t_orig
    while (true){ 
        // rejection algorithm: randomly sample the cube, 
        // not return until the vector falls within the sphere 
        double x = random_double(t_orig.x()-1, t_orig.x()+1); 
        double y = random_double(t_orig.y()-1, t_orig.y()+1); 
        double z = random_double(t_orig.z()-1, t_orig.z()+1); 
        Vec3<double> v(x,y,z);
        v = v - t_orig;  
        if (v.length() <=1.0) {
            return v; 
            }
    }
}


