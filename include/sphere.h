#pragma once

#include <memory>

#include "hittable.h"
#include "vec3.h"
#include "interval.h"
#include "material.h"

class Sphere:public hittable {
    private:
        Point3<double> center; 
        double radius; 
        std::shared_ptr<Material> mat; 
    public:
        // constructors 
        // Sphere() = default; 
        Sphere(const Point3<double>& _center, const double _radius, const std::shared_ptr<Material> t_material): 
            center(_center), radius(_radius), mat(t_material) {}
        Point3<double> get_center() {return center; }
        double get_radius() {return radius; }
  

        bool hit(Ray<double> ray_, Interval intv, HitRecord& rec) const override {
            auto ac = ray_.origin() - center; 
            auto a_pr = dot_product(ray_.direction(), ray_.direction());
            auto b_pr = 2*dot_product(ac, ray_.direction()); 
            auto c_pr = dot_product(ac, ac) - radius*radius; 
            auto discriminant = b_pr*b_pr-4*a_pr*c_pr; 
            if (discriminant<0) {return false; }
            else {
                
                rec.t = (-b_pr-std::sqrt(discriminant))/(2.0*a_pr);

                if (!intv.contains(rec.t)) {
                    rec.t = (-b_pr+std::sqrt(discriminant))/(2.0*a_pr);
                    if (!intv.contains(rec.t)) {return false;}
                }
                rec.P = ray_.at(rec.t); 
                rec.set_face_normal(ray_, (rec.P-center)/radius); 
                
                rec.material = mat; 
                return true;                 
            }
        }
};