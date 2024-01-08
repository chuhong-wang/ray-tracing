#pragma once
#include <cmath>
#include <random> 

const double infinity = std::numeric_limits<double>::infinity();
const double PI = 3.1415926535897932385;

template <typename T>
T degree_to_radian(T& degree_){
    return degree_/180.0*PI; 
}

template <typename T>
T random_double() {
    return static_cast<T>(std::rand())/RAND_MAX; 
}

// template <typename T>
// T random_double(T t_min, T t_max) {
//     return t_min + (t_max - t_min)*random_double<T>(); 
// }



