#include "aabb.h" 
#include "common.h"
#include "bvh_node.h"
#include "metal.h"
#include "sphere.h"
#include "hittable_list.h"

int main(){
    std::cout << "testing Aabb " ; 
    auto bbox = Aabb(Point3(-2-0.2,0.2-0.2,-2-0.2), Point3(-1+0.2,0.2+0.2,-2+0.2)); 
    std::cout << bbox.axis(0) << bbox.axis(1) << bbox.axis(2); 
    auto myRay2 = Ray(Point3(-0.5, 0.2, 0), Vector(-1.5,0.2,-2), 0.0);
    bool hit_aabb = bbox.hit(myRay2, Interval<float>(0, infinity)); 

    std::cout << hit_aabb << std::endl; 

    std::cout << "testing Bvh_node" << std::endl; 
    Hittable_list scene; 

    auto matrl = std::make_shared<Metal>(Color(0.5, 0.5, 0.5)); 
    // scene.add(std::make_shared<Sphere>(Point3(0.0, 1.0, -1.0), 1.0, matrl));

    int ij_bound = 4; 
    for (int a = -ij_bound; a<ij_bound; ++a) {
        for (int b = -ij_bound; b < ij_bound; ++b) {
            auto center = Point3(a, 0.2, b); 
            scene.add(std::make_shared<Sphere>(center, 0.2, matrl)); 
        }    
    }

    auto node = Bvh_node(scene); 
    // auto node = Hittable_list(std::make_shared<Bvh_node>(scene));

    auto myHitRecord = HitRecord();

    // std::cout << "test ray1" << std::endl; 
    // auto myRay1 = Ray(Point3(0, 0, 0), Vec3(100,100,1), 0.0);
    // auto res1 = node.hit(myRay1,Interval(0, infinity), myHitRecord); 
    // std::cout << res1 << std::endl; 

    // auto myRay2 = Ray(Point3(0, 0, 0), Vec3(0,1,-1), 0.0);
    std::cout << "test ray2" << std::endl; 
    auto res2 = node.hit(myRay2,Interval<float>(0, infinity), myHitRecord); 

    std::cout << res2 <<"record: "<<myHitRecord.P << std::endl; 

    myHitRecord = HitRecord();
    auto res3 = scene.hit(myRay2, Interval<float>(0, infinity), myHitRecord); 
    std::cout << res3 <<"record: "<<myHitRecord.P << std::endl; 
    return 0; 
}