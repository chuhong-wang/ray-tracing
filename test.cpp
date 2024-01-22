#include "aabb.h" 
#include "common.h"
#include "bvh_node.h"
#include "metal.h"
#include "sphere.h"
#include "hittable_list.h"
#include "color.h"
#include "camera.h"
#include "lambertian.h"

using std::cout, std::endl; 

void test_camera() {
    std::cout << "———————————————————— testing Camera ——————————————————————————————  \n";
    Camera cam; 
    cam.camera_lookAt = Point3(0, 0, 0); 
    cam.camera_lookFrom = Point3(1, 3, 0);
    Vector w = unit_vector(cam.camera_lookFrom - cam.camera_lookAt); 
    // std::cout << "w: " << w;
    // std::cout << "u: " << unit_vector(cross_product(w, w)); 
    cam.initialize(); 
    std::cout << "get_ray(0,0): " << cam.get_ray(0, 0).direction() << std::endl; 
} 

void test_diffuse_surface(){
    std::cout << "———————————————————— testing scatter ——————————————————————————————  \n";
    
    auto myRay = Ray(Point3(0, 0, -10), Vector(0, -1, -1), 0); 
    auto matrl_ground = std::make_shared<Lambertian>(Color(0.5, 0.5, 0.5)); 
    auto earth = Sphere(Point3(0.0, -1000, 0.0), 1000.0, matrl_ground); 
    
    auto myHitRecord = HitRecord(); 
    earth.hit(myRay, Interval2f(0, infinity), myHitRecord); 
    std::cout << "intersecting point: " << myHitRecord.P; 
    std::cout << "front face? " << myHitRecord.front_face; 

    Ray ray_scattered; 
    Color attenuation; 
    matrl_ground->scatter(myRay, myHitRecord, attenuation, ray_scattered); 
    std::cout << "ray_scattered direction: " << ray_scattered.direction();
    std::cout << dot_product(ray_scattered.direction(), myHitRecord.normal);  
}
int main(){
    
    test_camera(); 
    test_diffuse_surface(); 

    

    // std::cout << "———————————————————— testing Aabb —————————————————————————————— \n"; 
    // auto bbox = Aabb(Point3(-2-0.2,0.2-0.2,-2-0.2), Point3(-1+0.2,0.2+0.2,-2+0.2)); 
    // std::cout << "bounding value of bbox in 3 axes: " << bbox.axis(0) << bbox.axis(1) << bbox.axis(2); 
    // auto myRay2 = Ray(Point3(-0.5, 0.2, 0), Vector(-1.5,0,-2), 0.0);
    // bool hit_aabb = bbox.hit(myRay2, Interval<float>(0, infinity)); 

    // std::cout <<"ray hit bbox? -> expected 1; actural: " << hit_aabb << std::endl; 

    // std::cout << "———————————————————— testing Bvh_node —————————————————————————————— " << std::endl; 
    // Hittable_list scene; 

    // auto matrl = std::make_shared<Metal>(Color(0.5, 0.5, 0.5)); 

    // int ij_bound = 2; 
    // for (int a = -ij_bound; a<ij_bound; ++a) {
    //     for (int b = -ij_bound; b < ij_bound; ++b) {
    //         auto center = Point3(a, 0.2, b); 
    //         scene.add(std::make_shared<Sphere>(center, 0.2, matrl)); 
    //     }    
    // }
    // auto node = Bvh_node(scene); 
    // auto myHitRecord = HitRecord();

    // std::cout << "test ray2" << std::endl; 
    // auto res2 = node.hit(myRay2,Interval<float>(0, infinity), myHitRecord); 

    // std::cout << res2 <<"intersecting point w/ BVH : "<<myHitRecord.P << std::endl; 

    // myHitRecord = HitRecord();
    // auto res3 = scene.hit(myRay2, Interval<float>(0, infinity), myHitRecord); 
    // std::cout << res3 <<"intersecting point w/o BVH : "<<myHitRecord.P << std::endl; 


    // // std::cout << "————————————————————testing Color —————————————————————————————— " << std::endl; 
    // // Camera cam; 
    // // auto recc = cam.ray_color(myRay2, scene, 50);
    // // std::cout <<"recc: "<< recc; 


    // // std::cout << "---------------------testing vector -----------------------------" << std::endl; 
    // // auto unit_direction = unit_vector(Vector(1,1,1));
    // // auto a = 0.5f * (unit_direction.y() + 1.0f); 
    // // std::cout <<(1.0 - a) * Color(1.0, 1.0, 1.0) +
    // //       a * Color(0.5, 0.7, 1.0) <<std::endl; 
    
    // // auto b = 0.5 * (unit_direction.y() + 1.0); 
    // // std::cout <<(1.0 - b) * Color(1.0, 1.0, 1.0) +
    // //       b * Color(0.5, 0.7, 1.0) <<std::endl; 
    // return 0; 

}