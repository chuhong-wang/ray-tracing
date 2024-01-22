#pragma once
#include "ray.h"
#include "vec3.h"

// handle the circular include issue 
// #include "material.h" 

class Material; 

class HitRecord {
 public:
  // data members 
  float t;          // root of quandratic formula
  Point3 P;  // ray.at(t)
  Vector normal;
  bool front_face;
  std::shared_ptr<Material> material; 
  
  void set_face_normal(Ray& r_, const Vector& outward_normal) {
    front_face = (dot_product(r_.direction(), outward_normal) <= 0.0);
    normal = front_face ? outward_normal : -outward_normal;
  }
};