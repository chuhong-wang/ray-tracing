#pragma once
#include <cmath>

const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

template <typename T>
T degree_to_radian(T& degree_){
    return degree_/180.0*pi; 
}



