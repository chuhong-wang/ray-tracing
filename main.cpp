#include <iostream>
#include "common.h"
#include "vec3.h"
#include "color.h"
#include "ray.h"
#include "sphere.h"
#include "hittable_list.h"
#include "camera.h"
#include "lambertian.h"
#include "metal.h"

int main() {
    // // test random vector 
    // random_vector(Point3<double>(0,0,0)); 
    // camera 
    Camera camera; 
    camera.image_width = 400; 
    camera.aspect_ratio = 9.0/16.0; 
    camera.sample_neighbor_pixels = 50; 
    camera.reflectance = 0.8; 

    // world 
    Hittable_list hittable_list; 
    auto matl1 = std::make_shared<Lambertian>(Color<double>(0.5, 0.5, 0.5)); 
    auto matl2 = std::make_shared<Metal>(Color<double>(1, 1, 1)); 
    auto ptr1 = std::make_shared<Sphere>(Point3<double>(0,0,-1), 0.5,matl1); 
    auto ptr2 = std::make_shared<Sphere>(Point3<double>(0,-100.5,-1), 100, matl1); 
    auto ptr3 = std::make_shared<Sphere>(Point3<double>(1,0,-1), 0.5, matl2); 

    hittable_list.add(ptr1); 
    hittable_list.add(ptr2); 
    hittable_list.add(ptr3); 

    //renderer
    camera.render(hittable_list); 
    
}