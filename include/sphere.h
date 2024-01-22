#pragma once

#include <memory>

#include "hittable.h"
#include "vec3.h"
#include "interval.h"
#include "material.h"

class Sphere:public hittable {
    private:
        Point3 center; 
        Vector center_vec; 
        bool is_moving; 
        float radius; 
        std::shared_ptr<Material> mat; 
        Aabb bbox; 
        
    public:
        // constructors 
        // Sphere() = default; 

        // provide two center positions for moving spheres, one center positions for static spheres 
        Sphere(const Point3& t_center1, const float t_radius, const std::shared_ptr<Material> t_material):
            center(t_center1), center_vec(Vec3(0.0f,0.0f,0.0f)), radius(t_radius), mat(t_material), is_moving(false) {
                auto radius_vec = Vec3(radius, radius, radius); 
                bbox = Aabb(center-radius_vec, center+radius_vec); 
            }

        Sphere(const Point3& t_center1, const Point3& t_center2, const float t_radius, const std::shared_ptr<Material> t_material): 
            center(t_center1), center_vec(t_center2 - t_center1), radius(t_radius), mat(t_material), is_moving(true) {
                auto radius_vec = Vec3(radius, radius, radius); 
                bbox = Aabb(t_center1-radius_vec, t_center1+radius_vec); 
                bbox.add(Aabb(t_center2-radius_vec, t_center2+radius_vec));
            }
        
        Point3 get_center() {return center; }
        float get_radius() {return radius; }

        Aabb bounding_box() const override {
            return bbox; 
        }
  

        bool hit(Ray ray_, Interval2f intv, HitRecord& rec) const override {
            auto new_center = center; 
            // motion blurring 
            if(is_moving) {
                new_center = ray_.time()*center_vec + center; 
            }
            auto ac = ray_.origin() - new_center; 
            auto a_pr = dot_product(ray_.direction(), ray_.direction());
            auto b_pr = 2*dot_product(ac, ray_.direction()); 
            auto c_pr = dot_product(ac, ac) - radius*radius; 
            auto discriminant = b_pr*b_pr-4.0f*a_pr*c_pr;
            
            if (discriminant<0) {return false; }
            else {
                
                rec.t = (-b_pr-std::sqrt(discriminant))/(2.0*a_pr);

                if (!intv.contains(rec.t)) {
                    rec.t = (-b_pr+std::sqrt(discriminant))/(2.0*a_pr);
                    if (!intv.contains(rec.t)) {return false;}
                }
                rec.P = ray_.at(rec.t); 
                // auto p_verify = ray_.origin() + ray_.direction()*rec.t; 
                rec.set_face_normal(ray_, (rec.P-new_center)/radius); 
                
                rec.material = mat; 
                return true;                 
            }
        }

};