#pragma once

#include <iostream>
#include <string>
#include <cmath> 

#include "color.h"
#include "common.h"
#include "hittable.h"
#include "ray.h"
#include "vec3.h"

class Camera {
 public:
  // dimensions of image and viewport 
  double image_width = 100;
  double aspect_ratio = 9.0 / 16.0;
  int sample_neighbor_pixels = 10; 
  int max_reflection_depth = 10;  

  double vfov = 90; // vertical field of view  

  // location and orientation of camera
  Vec3<double> v_up = Vec3<double>(0, 1, 0);                      // reference up 

  Point3<double> camera_lookFrom = Point3<double>(0, 0, 0);
  Point3<double> camera_lookAt = Point3<double>(0, -1.0, -1.0);

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
    double theta = degree_to_radian(vfov);  
    double focal_length = (camera_lookAt - camera_lookFrom).length(); 
    double viewport_height = 2*tan(theta/2)*focal_length; 

    Vec3<double> w = unit_vector(camera_lookFrom - camera_lookAt);  // opposite view direction 
    Vec3<double> u = unit_vector(cross_product(v_up, w));           // camera right 
    Vec3<double> v =  cross_product(w, u);                          // camera up 
    
    viewport_width =
        viewport_height * static_cast<double>(image_width / image_height);
    viewport_u = u*viewport_width;
    viewport_v = -v*viewport_height;
    pixel_delta_u = viewport_u / static_cast<double>(image_width);
    pixel_delta_v = viewport_v / static_cast<double>(image_height);

    viewport_center = camera_lookFrom - focal_length * w;
    viewport_upper_left = camera_lookFrom - focal_length * w -
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
    Vec3<double> ray_direction = pixel_center - camera_lookFrom; 
    Ray ray_(camera_lookFrom, ray_direction); 
    return ray_; 
  }

 public:
  void initialize(){
    compute_image_height(); 
    compute_viewport(); 
  }

  Color<double> ray_color(Ray<double>& r, hittable& scene, int curr_depth) const {
    HitRecord rec;
    Ray<double> ray_scattered; 
    Color<double> attenuation; 

    if (curr_depth >=0 && scene.hit(r, Interval(zeroTolerence, infinity), rec) ) {
      if(rec.material->scatter(r, rec, attenuation, ray_scattered)){
        return attenuation*ray_color(ray_scattered, scene, --curr_depth); 
      }
      else { return Color<double>(0,0,0); }
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