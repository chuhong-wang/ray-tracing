#pragma once
#include "vec3.h"

const float infinity = std::numeric_limits<float>::infinity();
const float PI = 3.1415926535897932385;
const float zeroTolerence = 1e-4; // to treat shadow acne of matte object

template <typename T>
T degree_to_radian(const T& degree_){
    return degree_/180.0f*PI; 
}

template <typename T>
inline T random_double() {
    return static_cast<T>(rand()/(RAND_MAX + 1.0f)); 
}
template <typename T>
inline T random_double(T t_min, T t_max) {
    return t_min + (t_max - t_min)*random_double<T>(); 
}

Vector random_vector(const Point3& t_orig);

Vector random_vector_within_unit_disk();

template <typename T> 
void gamma_color(T& before_gamma){
    before_gamma = fmax(0.0, before_gamma); 
    before_gamma = std::sqrt(before_gamma); 
}



