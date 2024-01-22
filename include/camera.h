#pragma once

#include <iostream>
#include <string>
#include <cmath> 
#include <chrono>

#include "color.h"
#include "common.h"
#include "hittable.h"
#include "ray.h"
#include "vec3.h"

class Camera {
 public:
  // dimensions of image and viewport 
  float image_width = 100;
  float aspect_ratio = 9.0 / 16.0;
  int sample_neighbor_pixels = 20; 
  int max_reflection_depth = 20;  

  float vfov = 90; // vertical field of view  
  float defocus_angle = 10;    // defocus blur settings
  float focus_dist = 10; 

  float shutter_time = 0.01; 

  // location and orientation of camera
  Vector v_up = Vector(0.0f, 1.0f, 0.0f); // reference up 

  Point3 camera_lookFrom = Point3(0, 0, 0);
  Point3 camera_lookAt = Point3(0, -1.0, -1.0);


 private:
  // set up the image and viewport, functions will be called in initialize()
  float image_height, viewport_width;
  Vector viewport_u, viewport_v, pixel_delta_u, pixel_delta_v;
  Point3 viewport_upper_left, pixel00_loc;

  Vector u, v, w; 
  float defocus_disk_radius; 

  void compute_image_height() {
    image_height = static_cast<int>(image_width * aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;
  }
  void compute_viewport() {
    float theta = degree_to_radian(vfov);  
    float viewport_height = 2*tan(theta/2)*focus_dist; 

    auto aperture_angle = degree_to_radian(defocus_angle); 
    this->defocus_disk_radius = tan(aperture_angle/2) * focus_dist; 

    this->w = unit_vector(camera_lookFrom - camera_lookAt);  // opposite view direction 
    this->u = unit_vector(cross_product(v_up, w));           // camera right 
    this->v = cross_product(w, u);                          // camera up 
    
    viewport_width =
        viewport_height * static_cast<float>(image_width / image_height);
    viewport_u = u*viewport_width;
    viewport_v = -v*viewport_height;
    pixel_delta_u = viewport_u / static_cast<float>(image_width);
    pixel_delta_v = viewport_v / static_cast<float>(image_height);

    viewport_upper_left = camera_lookFrom - focus_dist * w -
                          viewport_u / 2.0f - viewport_v / 2.0f;
    pixel00_loc = viewport_upper_left + 0.5f * (pixel_delta_u + pixel_delta_v);

  }

  Vector sampleApoint_unitPixel(){
    Vector offSet = (-0.5f+ random_double<float>())*pixel_delta_u + (-0.5f+ random_double<float>())*pixel_delta_v; 
    return offSet; 
  }

  Point3 defocus_sample(const Point3& t_center) {
    auto rand_vector_onDisk = random_vector_within_unit_disk()*defocus_disk_radius; 
    // std::cout << "t_center" << t_center << "defocus shift" << (this->u)*rand_vector_onDisk[0] + (this->v)*rand_vector_onDisk[1]; 
    return t_center + (this->u)*rand_vector_onDisk[0] + (this->v)*rand_vector_onDisk[1]; 
  }

  // antialiasing utility function: get light around the specified pixel 
  public:
  Ray get_ray(int i, int j){
    Point3 pixel_center = pixel00_loc + (i*pixel_delta_u) + (j*pixel_delta_v);

    // sample surrounding pixelds for antialiasing  
    auto random_offSet = sampleApoint_unitPixel(); 
    pixel_center += random_offSet; 

    // defocus blurring 
    auto new_camera_lookFrom = defocus_angle<=0.0?camera_lookFrom:defocus_sample(camera_lookFrom); 
    Vector ray_direction = pixel_center - new_camera_lookFrom; 

    auto time = random_double<float>();  
    Ray ray_(new_camera_lookFrom, ray_direction, time); 

    return ray_; 
  }

 public:
  void initialize(){
    compute_image_height(); 
    compute_viewport(); 
  }

  Color ray_color(Ray& r, hittable& scene, int curr_depth) const {
    HitRecord rec;
    Ray ray_scattered; 
    Color attenuation; 
    if (curr_depth >=0 && scene.hit(r, Interval2f(zeroTolerence, infinity), rec) ) {
      if(rec.material->scatter(r, rec, attenuation, ray_scattered)){
        return attenuation*ray_color(ray_scattered, scene, --curr_depth); 
      }
      else { 
        return Color(0,0,0); }
    }
    Vector unit_direction = unit_vector(r.direction());
    auto a = 0.5f * (unit_direction.y() + 1.0f); 
    return (1.0f - a) * Color(1.0, 1.0, 1.0) +
          a * Color(0.5, 0.7, 1.0);
  }

  // Render
  void render(hittable& world) {
    initialize(); 
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
    for (int j = 0; j < image_height; ++j) {
      // measure running time 
      // auto startTime = std::chrono::high_resolution_clock::now();
      for (int i = 0; i < image_width; ++i) {
        // antialiasing by sampling light falling around each pixel in a 1x1 square 
        // std::cout << i << " " << j << std::endl; 
        Color pixel_color(0,0,0); 
        for (int sample = 0; sample < sample_neighbor_pixels; ++ sample){ 
            auto ray_ = get_ray(i, j); 
            pixel_color += ray_color(ray_, world, max_reflection_depth); 
        }
        pixel_color = pixel_color/static_cast<float>(sample_neighbor_pixels); 
        write_color(std::cout, pixel_color);
      }
      // auto currTime = std::chrono::high_resolution_clock::now();
      // auto duration = std::chrono::duration_cast<std::chrono::microseconds>(currTime - startTime).count();
      // std::clog << "height= " << j << ", end Time: " << duration << "\n";
    }
  }
};