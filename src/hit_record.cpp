#include "hittable.h"

void HitRecord::set_face_normal(Ray& r_, const Vector& outward_normal) {
    front_face = (dot_product(r_.direction(), outward_normal) <= 0.0);
    normal = front_face ? outward_normal : -outward_normal;
  }
