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

  void compute_image_height();
  void compute_viewport();

  Vector sampleApoint_unitPixel();

  Point3 defocus_sample(const Point3& t_center);

  // antialiasing utility function: get light around the specified pixel 
  public:
  Ray get_ray(int i, int j);

  void initialize();

  Color ray_color(Ray& r, hittable& scene, int curr_depth) const;

  // Render
  void render(hittable& world);
};