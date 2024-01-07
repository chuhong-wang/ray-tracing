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

        hit_record res; 

        bool hit(ray<double> ray_, double r_min, double r_max, hit_record& res) const override {
            auto ac = ray_.origin() - center; 
            auto a_pr = dot_product(ray_.direction(), ray_.direction());
            auto b_pr = 2*dot_product(ac, ray_.direction()); 
            auto c_pr = dot_product(ac, ac) - radius*radius; 
            auto discriminant = b_pr*b_pr-4*a_pr*c_pr; 
            if (discriminant<0) {return false; }
            else {
                res.t = (-b_pr-std::sqrt(discriminant))/(2.0*a_pr); 
                res.P = ray_.at(res.t); 
                res.set_face_normal(ray_, (res.P-center)/radius); 
                return true; 
            }
        }
};