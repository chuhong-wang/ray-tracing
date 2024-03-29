#include "metal.h"

// Metal::Metal(Color t_attenuation):attenuation(t_attenuation){}
// Metal::Metal(Color t_attenuation, float t_fuzz):attenuation(t_attenuation), fuzziness(t_fuzz<1?t_fuzz:1) {}

// // member function
// bool Metal::scatter(const Ray& ray_in, HitRecord& rec, 
//     Color& t_attenuation, Ray& ray_scattered ) const  { 
//         auto vec_scattered = reflect(ray_in.direction(), rec.normal);
//         ray_scattered = Ray(rec.P, vec_scattered, ray_in.time()); 
//         if(fuzziness>0.0){
//             auto random_unit_vec = random_vector(Vector(0, 0, 0)); 
//             auto fuzzed = unit_vector(random_unit_vec)*fuzziness + vec_scattered;
//             ray_scattered = Ray(rec.P, fuzzed, ray_in.time()); 
//         }
//         t_attenuation = attenuation; 
//         return true; 
// }