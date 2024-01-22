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
#include "bvh_node.h"

using std::shared_ptr, std::make_shared; 

int main() {
    // // test random vector 
    // random_vector(Point3(0,0,0)); 
    // camera 
    Camera camera; 
    camera.image_width = 400; 
    camera.sample_neighbor_pixels = 50; 

    camera.vfov = 40; 
    camera.camera_lookFrom = Point3(3, 3, 1);
    camera.camera_lookAt = Point3(0, 0, -1);

    camera.defocus_angle = 0.0; 
    camera.focus_dist = 13.26; 

    camera.shutter_time = 0.01; 
   

    // random sphere scattered around 
    auto matrl_ground = std::make_shared<Lambertian>(Color(0.5, 0.5, 0.5)); 

    Hittable_list scene;
    scene.add(std::make_shared<Sphere>(Point3(0.0, -10, 0.0), 10.0, matrl_ground)); 
    
    double sample_matrl; 
    int ij_bound = 2; 
    for (int a = -ij_bound; a<ij_bound; ++a) {
        for (int b = -ij_bound; b < ij_bound; ++b) {
            sample_matrl = random_double<float>(); 
            auto center = Point3(a, 0.2, b);
            shared_ptr<Material> matrl; 
            if (sample_matrl < 0.5) {
                matrl = make_shared<Lambertian>(Color(random_double<float>(), 1, 1)); 
            }
            else if (sample_matrl < 0.75) {
                matrl = make_shared<Metal>(Color(1, random_double<float>(), 1), random_double<float>(0, 0.5));
            }
            else {
                matrl = make_shared<Dielectric>(1.5); 
            }

            if(sample_matrl > 0.2){ scene.add(make_shared<Sphere>(center,center+Vector(0, random_double<float>(0, 0.5), 0), 0.2, matrl)); }

            else { scene.add(make_shared<Sphere>(center, 0.2, matrl)); }
        }    
    }

    //renderer
    camera.render(scene); 

    // apply BVH algo
    // auto world = Bvh_node(scene); 
    // camera.render(world); 
    
}