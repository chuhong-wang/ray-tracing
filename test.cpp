#include "aabb.h" 
#include "common.h"
#include "bvh_node.h"
#include "metal.h"
#include "sphere.h"
#include "hittable_list.h"

int main(){
    std::cout << "testing Aabb " ; 
    auto bbox = Aabb(Point3<double>(-1,0,-2), Point3<double>(1,2,0)); 
    auto myRay2 = Ray<double>(Point3<double>(0, 0, 0), Vec3<double>(-2,1,-1), 0.0);
    bool hit_aabb = bbox.hit(myRay2, Interval(0, infinity)); 

    std::cout << hit_aabb << std::endl; 

    std::cout << "testing Bvh_node" << std::endl; 
    Hittable_list scene; 
    auto matrl = std::make_shared<Metal>(Color<double>(0.5, 0.5, 0.5)); 
    scene.add(std::make_shared<Sphere>(Point3<double>(0.0, 1.0, -1.0), 1.0, matrl));
    scene.add(std::make_shared<Sphere>(Point3<double>(2.0, 1.0, -1.0), 1.0, matrl));
    scene.add(std::make_shared<Sphere>(Point3<double>(-2.0, 1.0, -1.0), 1.0, matrl));

    auto node = Bvh_node(scene); 
    // auto node = Hittable_list(std::make_shared<Bvh_node>(scene));

    auto myHitRecord = HitRecord();

    std::cout << "test ray1" << std::endl; 
    auto myRay1 = Ray<double>(Point3<double>(0, 0, 0), Vec3<double>(100,100,1), 0.0);
    auto res1 = node.hit(myRay1,Interval(0, infinity), myHitRecord); 
    std::cout << res1 << std::endl; 

    // auto myRay2 = Ray<double>(Point3<double>(0, 0, 0), Vec3<double>(0,1,-1), 0.0);
    std::cout << "test ray2" << std::endl; 
    auto res2 = node.hit(myRay2,Interval(0, infinity), myHitRecord); 

    std::cout << res2  << std::endl; 
    return 0; 
}