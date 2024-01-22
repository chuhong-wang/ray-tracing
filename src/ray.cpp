#include "ray.h"

// constructor
Ray::Ray() {}
Ray::Ray(const Point3f& t_origin, const Point3f& t_direction, const float t_time):
    orig(t_origin), dir(t_direction), ray_time(t_time) {}


// member functions 
Point3f Ray::origin() const {return this->orig; }
Vector3f Ray::direction() const {return this->dir; }
float Ray::time() const {return this->ray_time; }
Vector3f Ray::at(float t) {
    return orig + dir*t; 
}