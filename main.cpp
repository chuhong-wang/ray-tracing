#include <iostream>
#include "common.h"
#include "vec3.h"
#include "color.h"
#include "ray.h"
#include "sphere.h"
#include "hittable_list.h"
#include "camera.h"

int main() {
    // // test random vector 
    // random_vector(Point3<double>(0,0,0)); 

    // camera 
    Camera camera; 
    camera.image_width = 800; 
    camera.aspect_ratio = 4.0/16.0; 
    camera.sample_neighbor_pixels = 50; 

    // world 
    Hittable_list hittable_list; 
    auto ptr1 = std::make_shared<Sphere>(Point3<double>(0,0,-1), 0.5); 
    auto ptr2 = std::make_shared<Sphere>(Point3<double>(0,-100.5,-1), 100); 
    auto ptr3 = std::make_shared<Sphere>(Point3<double>(1,0,-1), 0.5); 
    hittable_list.add(ptr1); 
    hittable_list.add(ptr2); 
    hittable_list.add(ptr3); 

    //renderer
    camera.render(hittable_list); 
    
}