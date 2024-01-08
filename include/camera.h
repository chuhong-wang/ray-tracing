#pragma once

#include <iostream>

#include "color.h"
#include "common.h"
#include "hittable.h"
#include "ray.h"
#include "vec3.h"

Color<double> ray_color(Ray<double>& r, hittable& obj) {
  HitRecord res;
  if (obj.hit(r, Interval(0, infinity), res)) {
    return 0.5 * (res.normal + Color<double>(1, 1, 1));
  }
  Vec3<double> unit_direction = unit_vector(r.direction());
  auto a = 0.5 * (unit_direction.y() + 1.0);
  return (1.0 - a) * Color<double>(1.0, 1.0, 1.0) +
         a * Color<double>(0.5, 0.7, 1.0);
}

class Camera {
 public:
  // data members
  double image_width = 800;
  double aspect_ratio = 9.0 / 16.0;
  int sample_neighbor_pixels = 10; 

  double viewport_height = 2.0;
  double focal_length = 1.0;
  Point3<double> camera_center = Point3<double>(0, 0, 0);

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

  Ray<double> get_ray(int i, int j){
    Point3<double> pixel_center = pixel00_loc + (i*pixel_delta_u) + (j*pixel_delta_v); 
    auto random_offSet = sampleApoint_unitPixel(); 
    pixel_center += random_offSet; 
    Vec3<double> ray_direction = pixel_center - camera_center; 
    Ray ray_(camera_center, ray_direction); 
    return ray_; 
  }

 public:
  void initialize(){
    compute_image_height(); 
    compute_viewport(); 
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
          pixel_color += ray_color(ray_, world); 
        }
        
        pixel_color = pixel_color/static_cast<double>(sample_neighbor_pixels); 
        write_color(std::cout, pixel_color);
      }
    }
  }
};