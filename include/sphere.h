#pragma once

#include <memory>

#include "hittable.h"
#include "vec3.h"
#include "interval.h"
#include "material.h"

class Sphere:public hittable {
    private:
        Point3<double> center; 
        Vec3<double> center_vec; 
        bool is_moving; 
        double radius; 
        std::shared_ptr<Material> mat; 

        
    public:
        // constructors 
        // Sphere() = default; 

        // provide two center positions for moving spheres, one center positions for static spheres 
        Sphere(const Point3<double>& t_center1, const double t_radius, const std::shared_ptr<Material> t_material):
            center(t_center1), center_vec(Vec3<double>(0,0,0)), radius(t_radius), mat(t_material), is_moving(false) {}

        Sphere(const Point3<double>& t_center1, const Point3<double>& t_center2, const double t_radius, const std::shared_ptr<Material> t_material): 
            center(t_center1), center_vec(t_center2 - t_center1), radius(t_radius), mat(t_material), is_moving(true) {}
        
        Point3<double> get_center() {return center; }
        double get_radius() {return radius; }
  

        bool hit(Ray<double> ray_, Interval intv, HitRecord& rec) const override {

            auto new_center = center; 
            // motion blurring 
            if(is_moving) {
                new_center = ray_.time()*center_vec + center; 
            }

            auto ac = ray_.origin() - new_center; 
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
                rec.set_face_normal(ray_, (rec.P-new_center)/radius); 
                
                rec.material = mat; 
                return true;                 
            }
        }
};