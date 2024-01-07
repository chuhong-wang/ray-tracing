#include "hittable.h"
#include "vec3.h"

class Sphere:public hittable {
    private:
        point3<double> center; 
        double radius; 
    public:
        // constructors 
        // Sphere() = default; 
        Sphere(const point3<double>& _center, const double _radius): center(_center), radius(_radius) {}
        point3<double> get_center() {return center; }
        double get_radius() {return radius; }

        hit_record rec; 

        bool hit(ray<double> ray_, double ray_t_min, double ray_t_max, hit_record& rec) const override {
            auto ac = ray_.origin() - center; 
            auto a_pr = dot_product(ray_.direction(), ray_.direction());
            auto b_pr = 2*dot_product(ac, ray_.direction()); 
            auto c_pr = dot_product(ac, ac) - radius*radius; 
            auto discriminant = b_pr*b_pr-4*a_pr*c_pr; 
            if (discriminant<0) {return false; }
            else {
                rec.t = (-b_pr-std::sqrt(discriminant))/(2.0*a_pr);

                if (rec.t <=ray_t_min || rec.t >= ray_t_max) {
                    rec.t = (-b_pr+std::sqrt(discriminant))/(2.0*a_pr);
                    if (rec.t <=ray_t_min || rec.t >= ray_t_max) {return false;}
                }
                rec.P = ray_.at(rec.t); 
                rec.set_face_normal(ray_, (rec.P-center)/radius); 
                return true;                 
            }
        }
};