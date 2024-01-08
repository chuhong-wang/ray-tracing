#pragma once
#include "ray.h"
#include "vec3.h"

class HitRecord {
 public:
  double t;          // root of quandratic formula
  Point3<double> P;  // ray.at(t)
  Vec3<double> normal;
  bool front_face;

  void set_face_normal(Ray<double>& r_, const Vec3<double>& outward_normal) {
    front_face = (dot_product(r_.direction(), outward_normal) <= 0.0);
    normal = front_face ? outward_normal : -outward_normal;
  }
};