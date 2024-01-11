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
    Hittable_list scene;

    auto matrl_ground = std::make_shared<Lambertian>(Color<double>(0.8, 0.8, 0.0)); 
    auto matrl_center_sphere = std::make_shared<Lambertian>(Color<double>(0.7, 0.3, 0.3), 0.3); 
    auto matrl_left_sphere = std::make_shared<Metal>(Color<double>(0.8,0.8,0.8), 0.3); 
    auto matrl_right_sphere = std::make_shared<Metal>(Point3<double>(0.8, 0.6, 0.2), 1.0);

    scene.add(std::make_shared<Sphere>(Point3<double>(0.0, -100.5, -1.0), 100.0, matrl_ground)); 
    scene.add(std::make_shared<Sphere>(Point3<double>(0.0, 0.0, -1.0), 0.5, matrl_center_sphere)); 
    scene.add(std::make_shared<Sphere>(Point3<double>(-1.0, 0.0, -1.0), 0.5, matrl_left_sphere)); 
    scene.add(std::make_shared<Sphere>(Point3<double>(1.0, 0.0, -1.0), 0.5, matrl_right_sphere));

    //renderer
    camera.render(scene); 
    
}