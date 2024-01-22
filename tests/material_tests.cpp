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