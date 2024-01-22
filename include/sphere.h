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
        Sphere(const Point3& t_center1, const float t_radius, const std::shared_ptr<Material> t_material); 

        Sphere(const Point3& t_center1, const Point3& t_center2, const float t_radius, const std::shared_ptr<Material> t_material); 
        
        Point3 get_center(); 
        float get_radius();

        Aabb bounding_box() const override; 
  

        bool hit(Ray ray_, Interval2f intv, HitRecord& rec) const override; 

};