#pragma once
#include <cmath>
#include <iostream>

template <typename T>
class Vec3 {
    private: 
        // data member
        T v[3];

    public:
        // constructor 
        Vec3() {v[0] = 0; v[1]= 0; v[2]=0;}
        Vec3(T v0, T v1, T v2) { v[0] = v0; v[1] = v1; v[2] = v2; }

        // member functions 
        T x() const {return v[0];} // use const since the function doesn't alter the state of the object
        T y() const {return v[1];}
        T z() const {return v[2];}
        T length() const {return std::sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]); }; 
        T length_square()  {return v[0]*v[0] + v[1]*v[1] + v[2]*v[2]; }; 

        // operator overloading
        Vec3 operator+() const {return *this;}
        Vec3 operator-() const {return Vec3(-v[0], -v[1], -v[2]); }
        T operator[](int i) {return v[i]; }
        T operator[](int i) const {return v[i]; }
        Vec3& operator+=(const Vec3& v2) {
            v[0]+= v2.v[0]; 
            v[1]+= v2.v[1]; 
            v[2]+= v2.v[2];
            return *this; }

        Vec3& operator+=(const T m) {
            v[0]+=m; 
            v[1]+= m; 
            v[2]+= m; 
            return *this;}
        
        Vec3& operator-=(Vec3& v2) {
            v[0]-= v2.v[0]; // v2.v[0] is the same as v2[0] due to the [] overloading
            v[1]-= v2.v[1]; 
            v[2]-= v2.v[2];
            return *this; } 

        Vec3& operator-=(const T m) {
            *this += -m; 
            return *this; } 
        
        Vec3& operator*=(Vec3& v2) {
            v[0]*= v2.v[0]; 
            v[1]*= v2.v[1]; 
            v[2]*= v2.v[2];
            return *this; }

        Vec3& operator*=(const T m) {
            v[0]*= m; 
            v[1]*= m; 
            v[2]*= m; 
            return *this; }
};

template <typename T>
using Point3 = Vec3<T>; 

template <typename T>
std::ostream& operator<<(std::ostream& os,  const Vec3<T>& v) {
    os << v.x() << " " << v.y() << " " << v.z() << '\n';  
    return os; 
} 

template <typename T> 
inline Vec3<T> operator+(const Vec3<T>& v1, const Vec3<T>& v2) {
    return Vec3<T>(v1[0]+v2[0], v1[1]+v2[1], v1[2]+v2[2]); 
}

template <typename T> 
inline Vec3<T> operator-(const Vec3<T>& v1, const Vec3<T>& v2) {
    return Vec3<T>(v1[0]-v2[0], v1[1]-v2[1], v1[2]-v2[2]); 
}

template <typename T> 
inline Vec3<T> operator*(const Vec3<T>& v1, const Vec3<T>& v2) {
    return Vec3<T>(v1[0]*v2[0], v1[1]*v2[1], v1[2]*v2[2]); 
}

template <typename T> 
inline Vec3<T> operator*(const Vec3<T>& v1, const T m) {
    return Vec3<T>(v1[0]*m, v1[1]*m, v1[2]*m); 
}
template <typename T> 
inline Vec3<T> operator*(const Vec3<T>& v1, const int m) {
    return Vec3<T>(v1[0]*m, v1[1]*m, v1[2]*m); 
}
template <typename T> 
inline Vec3<T> operator*(const T m, const Vec3<T>& v1) {
    return Vec3<T>(v1[0]*m, v1[1]*m, v1[2]*m); 
}
template <typename T> 
inline Vec3<T> operator*(const int m, const Vec3<T>& v1) {
    return Vec3<T>(v1[0]*m, v1[1]*m, v1[2]*m); 
}

template <typename T> 
inline Vec3<T> operator/(const Vec3<T>& v1, const T m) {
    return Vec3<T>(v1[0]/m, v1[1]/m, v1[2]/m); 
}

template <typename T> 
inline T dot_product(const Vec3<T>& v1, const Vec3<T>& v2) {
    return v1[0]*v2[0] + v1[1]*v2[1] + v1[2]*v2[2]; 
}

template <typename T> 
inline T cross_product(const Vec3<T>& v1, const Vec3<T>& v2) {
    return Vec3(v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1],
                v1.e[2] * v2.e[0] - v1.e[0] * v2.e[2],
                v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0]);
}

template <typename T>
inline Vec3<T> unit_vector(const Vec3<T>& v){
    return v/v.length(); 
}