#pragma once

#include <iostream>
#include <string>

#include "color.h"
#include "common.h"
#include "hittable.h"
#include "ray.h"
#include "vec3.h"

class Camera {
 public:
  // data members
  double image_width = 100;
  double aspect_ratio = 9.0 / 16.0;
  int sample_neighbor_pixels = 10; 
  int max_reflection_depth = 10; 
  double reflectance = 0.5; 

  double viewport_height = 2.0;
  double focal_length = 1.0;
  Point3<double> camera_center = Point3<double>(0, 0, 0);
  
  // "Random" samples a uniform distribution of random vector on a hemisphere
  // "Lambertian" samples vectors on a contact unit sphere, results in higher probability near object normal and lower probability near surface
  std::string reflection_random_mode = "Random";

 private:
  // set up the image and viewport, functions will be called in initialize()
  double image_height, viewport_width;
  Vec3<double> viewport_u, viewport_v, pixel_delta_u, pixel_delta_v;
  Point3<double> viewport_center, viewport_upper_left, pixel00_loc;

  void compute_image_height() {
    image_height = static_cast<int>(image_width * aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;
  }
  void compute_viewport() {
    viewport_width =
        viewport_height * static_cast<double>(image_width / image_height);
    viewport_u = Vec3<double>(viewport_width, 0, 0);
    viewport_v = Vec3<double>(0, -viewport_height, 0);
    pixel_delta_u = viewport_u / static_cast<double>(image_width);
    pixel_delta_v = viewport_v / static_cast<double>(image_height);
    viewport_center = camera_center + Vec3<double>(0, 0, focal_length);
    viewport_upper_left = camera_center - Vec3<double>(0, 0, focal_length) -
                          viewport_u / 2.0 - viewport_v / 2.0;
    pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
  }

  Vec3<double> sampleApoint_unitPixel(){
    Vec3<double> offSet = (-0.5+ random_double<double>())*pixel_delta_u + (-0.5+ random_double<double>())*pixel_delta_v; 
    return offSet; 
  }

  // antialiasing utility function: get light around the specified pixel 
  Ray<double> get_ray(int i, int j){
    Point3<double> pixel_center = pixel00_loc + (i*pixel_delta_u) + (j*pixel_delta_v); 
    auto random_offSet = sampleApoint_unitPixel(); 
    pixel_center += random_offSet; 
    Vec3<double> ray_direction = pixel_center - camera_center; 
    Ray ray_(camera_center, ray_direction); 
    return ray_; 
  }

  Vec3<double> reflection_vector(const Point3<double>& intersecting_point, const Vec3<double>& normal) const {
    if(reflection_random_mode=="Random"){
      Vec3<double> reflection_vec = random_vector(intersecting_point); 
      reflection_vec = unit_vector(reflection_vec); 
      reflection_vec = dot_product(reflection_vec, normal)>=0? reflection_vec:-reflection_vec; 
      return reflection_vec; 
    }
    else if(reflection_random_mode=="Lambertian"){
      auto unit_normal = unit_vector(normal);
      auto contactSphere_center = intersecting_point + unit_normal; 
      auto point_on_contactSphere = contactSphere_center + random_vector(contactSphere_center); 
      auto reflection_vec = point_on_contactSphere - intersecting_point;
      return reflection_vec; 
    }
    else {std::cerr << "invalid reflection mode" << std::endl; } 
  }

 public:
  void initialize(){
    compute_image_height(); 
    compute_viewport(); 
  }

  Color<double> ray_color(Ray<double>& r, hittable& obj, int curr_depth) const {
    HitRecord res;
    if (obj.hit(r, Interval(zeroTolerence, infinity), res) ) {
      Vec3<double> reflection_ray = reflection_vector(res.P, res.normal);   
      Ray re_ray = Ray(res.P, reflection_ray); 
      return reflectance * ray_color(re_ray, obj, --curr_depth); 
    }
    Vec3<double> unit_direction = unit_vector(r.direction());
    auto a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a) * Color<double>(1.0, 1.0, 1.0) +
          a * Color<double>(0.5, 0.7, 1.0);
  }

  // Render
  void render(hittable& world) {
    initialize(); 
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    for (int j = 0; j < image_height; ++j) {
      for (int i = 0; i < image_width; ++i) {
        // antialiasing by sampling light falling around each pixel in a 1x1 square 
        Color<double> pixel_color(0,0,0); 
        for (int sample = 0; sample < sample_neighbor_pixels; ++ sample){ 
          auto ray_ = get_ray(i, j); 
          pixel_color += ray_color(ray_, world, max_reflection_depth); 
        }
        
        pixel_color = pixel_color/static_cast<double>(sample_neighbor_pixels); 
        write_color(std::cout, pixel_color);
      }
    }
  }
};