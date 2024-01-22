#include "sphere.h"
#include "lambertian.h"
#include "gtest/gtest.h"
#include "color.h"

TEST(RayTracerTest, SphereIntersection1) {
    auto matrl = std::make_shared<Lambertian>(Color(0.5, 0.5, 0.5)); 
    Sphere sphere(Point3(0.0, 1.0, 1.0), 1.0, matrl);

    // 1. incoming ray normal to the surface 
    Ray myRay(Point3(0.0,1.0,-2.0), Vector(0, 0, 1), 0);
    HitRecord hitrecord; 
    bool intersectionResult = sphere.hit(myRay, Interval<float>(zeroTolerence, infinity), hitrecord); 
    ASSERT_TRUE(intersectionResult); 
    ASSERT_TRUE(hitrecord.front_face); 
    ASSERT_NEAR(hitrecord.t, 2, zeroTolerence);
    
    ASSERT_NEAR(hitrecord.P[0], 0.0f, zeroTolerence); 
    ASSERT_NEAR(hitrecord.P[1], 1.0f, zeroTolerence); 
    ASSERT_NEAR(hitrecord.P[2], 0.0f, zeroTolerence); 

    ASSERT_NEAR(hitrecord.normal[0], 0.0f, zeroTolerence); 
    ASSERT_NEAR(hitrecord.normal[1], 0.0f, zeroTolerence); 
    ASSERT_NEAR(hitrecord.normal[2], -1.0f, zeroTolerence); 
}

TEST(RayTracerTest, SphereIntersection2) {
    // 2. incoming ray hit the surface at angle != 90 degree 
    auto matrl = std::make_shared<Lambertian>(Color(0.5, 0.5, 0.5)); 
    Sphere sphere(Point3(0.0, 1.0, 1.0), 1.0, matrl);

    auto intersectionP = Point3(0.8, 0.5, 0.668338);  // pre-computed reference
    auto intersectionNormal = unit_vector(intersectionP - Point3(0.0,1.0,1.0)); // pre-computed reference

    HitRecord hitrecord; 
    Ray myRay2(Point3(0.0, 0.5, -2.0), intersectionP-Point3(0.0, 0.5, -2.0), 0); 
    bool intersectionResult = sphere.hit(myRay2, Interval<float>(zeroTolerence, infinity), hitrecord); 
    ASSERT_TRUE(intersectionResult); 
    ASSERT_TRUE(hitrecord.front_face); 

    ASSERT_NEAR(hitrecord.t, 1, zeroTolerence);
     
    ASSERT_NEAR(hitrecord.P[0], intersectionP[0], zeroTolerence); 
    ASSERT_NEAR(hitrecord.P[1], intersectionP[1], zeroTolerence); 
    ASSERT_NEAR(hitrecord.P[2], intersectionP[2], zeroTolerence); 


    ASSERT_NEAR(hitrecord.normal[0], intersectionNormal[0], zeroTolerence); 
    ASSERT_NEAR(hitrecord.normal[1], intersectionNormal[1], zeroTolerence); 
    ASSERT_NEAR(hitrecord.normal[2], intersectionNormal[2], zeroTolerence); 
}

#include "sphere.h"
#include "material.h"
#include "lambertian.h"
#include "metal.h"
#include "dielectric.h"
#include "gtest/gtest.h"

TEST(RayTracerTest, MaterialReflection){
    Ray myRay(Point3(0.0,1.0,-2.0), Vector(0, 0, 1), 0);
    HitRecord hitrecord;
    hitrecord.normal = unit_vector(Vector(2, -1, 3));
    hitrecord.P = Point3(0.8, 0.5, 0.668338); 
    hitrecord.front_face = true; 

    Color attenuation; Ray ray_scattered; 
    auto matrl = Lambertian(Color(0.5, 0.5, 0.5)); 
    bool scatter_res = matrl.scatter(myRay, hitrecord, attenuation, ray_scattered);

    
    ASSERT_GE(dot_product(ray_scattered.direction(), hitrecord.normal), 0.0f); 
    
}