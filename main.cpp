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
#include "dielectric.h"

using std::shared_ptr, std::make_shared; 

int main() {
    // // test random vector 
    // random_vector(Point3<double>(0,0,0)); 
    // camera 
    Camera camera; 
    camera.image_width = 400; 
    camera.sample_neighbor_pixels = 50; 
    // camera.reflectance = 0.8; 

    camera.vfov = 20; 
    camera.camera_lookFrom = Point3<double>(13, 3, 2);
    camera.camera_lookAt = Point3<double>(0, 0, 0);

    // world 
    Hittable_list scene;

    // // table salt on a table 
    // auto matrl_sodium = std::make_shared<Metal>(Color<double>(1, 0, 0.2), 0.0); 
    // auto matrl_chlorine = std::make_shared<Metal>(Color<double>(0, 1, 0.2), 0.1); 
    // auto matrl_ground = std::make_shared<Metal>(Color<double>(0.5, 0.5, 0.5), 0.2); 

    // scene.add(std::make_shared<Sphere>(Point3<double>(0.0, -1000.5, -1.0), 1000.0, matrl_ground)); 
    // scene.add(std::make_shared<Sphere>(Point3<double>(0.0, 0.0, -1.0), 0.5, matrl_chlorine)); 
    // scene.add(std::make_shared<Sphere>(Point3<double>(-1.0, 0.0, -1.0), 0.2, matrl_sodium)); 
    // scene.add(std::make_shared<Sphere>(Point3<double>(0.0, 1.0, -1.0), 0.2, matrl_sodium)); 
    // scene.add(std::make_shared<Sphere>(Point3<double>(-1.0, 1.0, -1.0), 0.5, matrl_chlorine));

    // scene.add(std::make_shared<Sphere>(Point3<double>(0.0, 0.0, -2.0), 0.2, matrl_sodium)); 
    // scene.add(std::make_shared<Sphere>(Point3<double>(-1.0, 0.0, -2.0), 0.5,matrl_chlorine )); 
    // scene.add(std::make_shared<Sphere>(Point3<double>(0.0, 1.0, -2.0), 0.5, matrl_chlorine)); 
    // scene.add(std::make_shared<Sphere>(Point3<double>(-1.0, 1.0, -2.0), 0.2, matrl_sodium));

    // random sphere scattered around 
    auto matrl_ground = std::make_shared<Lambertian>(Color<double>(0.5, 0.5, 0.5)); 
    scene.add(std::make_shared<Sphere>(Point3<double>(0.0, -1000, 0.0), 1000.0, matrl_ground)); 
    
    double sample_matrl; 

    for (int a = -2; a<2; ++a) {
        for (int b = -2; b < 2; ++b) {
            sample_matrl = random_double<double>(); 
            auto center = Point3<double>(a, 0.2, b); 
            shared_ptr<Material> matrl; 
            if (sample_matrl < 0.5) {
                matrl = make_shared<Lambertian>(Color<double>(random_double<double>(), 1, 1)); 
            }
            else if (sample_matrl < 0.75) {
                matrl = make_shared<Metal>(Color<double>(1, random_double<double>(), 1), random_double<double>(0, 0.5));
            }
            else {
                matrl = make_shared<Dielectric>(1.5); 
            }
            scene.add(make_shared<Sphere>(center, 0.2, matrl)); 
        }
    }

    //renderer

    camera.render(scene); 
    
}