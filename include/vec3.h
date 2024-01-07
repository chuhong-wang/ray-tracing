#pragma once
#include <cmath>
#include <iostream>

template <typename T>
class vec3 {
    private: 
        // data member
        T v[3];

    public:
        // constructor 
        vec3() {v[0] = 0; v[1]= 0; v[2]=0;}
        vec3(T v0, T v1, T v2) { v[0] = v0; v[1] = v1; v[2] = v2; }

        // member functions 
        T x() const {return v[0];} // use const since the function doesn't alter the state of the object
        T y() const {return v[1];}
        T z() const {return v[2];}
        T length() const {return std::sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]); }; 
        T length_square()  {return v[0]*v[0] + v[1]*v[1] + v[2]*v[2]; }; 

        // operator overloading
        vec3 operator+() const {return *this;}
        vec3 operator-() const {return vec3(-v[0], -v[1], -v[2]); }
        T operator[](int i) {return v[i]; }
        T operator[](int i) const {return v[i]; }
        vec3& operator+=(vec3& v2) {
            v[0]+= v2.v[0]; 
            v[1]+= v2.v[1]; 
            v[2]+= v2.v[2];
            return *this; }

        vec3& operator+=(const T m) {
            v[0]+=m; 
            v[1]+= m; 
            v[2]+= m; 
            return *this;}
        
        vec3& operator-=(vec3& v2) {
            v[0]-= v2.v[0]; // v2.v[0] is the same as v2[0] due to the [] overloading
            v[1]-= v2.v[1]; 
            v[2]-= v2.v[2];
            return *this; } 

        vec3& operator-=(const T m) {
            *this += -m; 
            return *this; } 
        
        vec3& operator*=(vec3& v2) {
            v[0]*= v2.v[0]; 
            v[1]*= v2.v[1]; 
            v[2]*= v2.v[2];
            return *this; }

        vec3& operator*=(const T m) {
            v[0]*= m; 
            v[1]*= m; 
            v[2]*= m; 
            return *this; }
};

template <typename T>
using point3 = vec3<T>; 

template <typename T>
std::ostream& operator<<(std::ostream& os,  const vec3<T>& v) {
    os << v.x() << " " << v.y() << " " << v.z() << '\n';  
    return os; 
} 

template <typename T> 
inline vec3<T> operator+(const vec3<T>& v1, const vec3<T>& v2) {
    return vec3<T>(v1[0]+v2[0], v1[1]+v2[1], v1[2]+v2[2]); 
}

template <typename T> 
inline vec3<T> operator-(const vec3<T>& v1, const vec3<T>& v2) {
    return vec3<T>(v1[0]-v2[0], v1[1]-v2[1], v1[2]-v2[2]); 
}

template <typename T> 
inline vec3<T> operator*(const vec3<T>& v1, const vec3<T>& v2) {
    return vec3<T>(v1[0]*v2[0], v1[1]*v2[1], v1[2]*v2[2]); 
}

template <typename T> 
inline vec3<T> operator*(const vec3<T>& v1, const T m) {
    return vec3<T>(v1[0]*m, v1[1]*m, v1[2]*m); 
}
template <typename T> 
inline vec3<T> operator*(const vec3<T>& v1, const int m) {
    return vec3<T>(v1[0]*m, v1[1]*m, v1[2]*m); 
}
template <typename T> 
inline vec3<T> operator*(const T m, const vec3<T>& v1) {
    return vec3<T>(v1[0]*m, v1[1]*m, v1[2]*m); 
}
template <typename T> 
inline vec3<T> operator*(const int m, const vec3<T>& v1) {
    return vec3<T>(v1[0]*m, v1[1]*m, v1[2]*m); 
}

template <typename T> 
inline vec3<T> operator/(const vec3<T>& v1, const T m) {
    return vec3<T>(v1[0]/m, v1[1]/m, v1[2]/m); 
}

template <typename T> 
inline T dot_product(const vec3<T>& v1, const vec3<T>& v2) {
    return v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2]; 
}

template <typename T> 
inline T cross_product(const vec3<T>& v1, const vec3<T>& v2) {
    return vec3(v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1],
                v1.e[2] * v2.e[0] - v1.e[0] * v2.e[2],
                v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0]);
}

template <typename T>
inline vec3<T> unit_vector(const vec3<T>& v){
    return v/v.length(); 
}