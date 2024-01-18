#include "gtest/gtest.h"
#include "aabb.h" 
#include "bvh_node.h"
#include "lambertian.h"
#include "sphere.h"
#include "hittable_list.h"

TEST(BVH, bbox_test) {
    auto t = Aabb(Interval(0, 1), Interval(0,1), Interval(0,1)); 
    auto myRay1 = Ray<double>(Vec3<double>(0,0,0), Vec3<double>(0.5,0.5,0.5), 0.0); 
    EXPECT_TRUE(t.hit(myRay1));

    auto myRay2 = Ray<double>(Vec3<double>(0,0,0), Vec3<double>(-0.5,-0.5,0.5), 0.0); 
    EXPECT_FALSE(t.hit(myRay2)); 
}

TEST(BVH, Bvh_node_test) {
    Hittable_list scene; 
    auto matrl = std::make_shared<Lambertian>(Color<double>(0.5, 0.5, 0.5)); 
    scene.add(std::make_shared<Sphere>(Point3<double>(0.0, 1.0, -1.0), 1.0, matrl));
    scene.add(std::make_shared<Sphere>(Point3<double>(2.0, 1.0, -1.0), 1.0, matrl));
    scene.add(std::make_shared<Sphere>(Point3<double>(-2.0, 1.0, -1.0), 1.0, matrl));

    auto node = Bvh_node(scene); 

    auto myHitRecord = HitRecord();
    auto myRay1 = Ray<double>(Point3<double>(0,0,0), Vec3<double>(100,100,1), 0.0);
    EXPECT_FALSE(node.hit(myRay1,Interval(0, infinity), myHitRecord)); 

    auto myRay2 = Ray<double>(Point3<double>(0,1.0,-1.0), Vec3<double>(0,1,-1), 0.0);
    EXPECT_TRUE(node.hit(myRay2,Interval(0, infinity), myHitRecord)); 
}