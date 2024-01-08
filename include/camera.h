#pragma once 

#include <iostream>
#include "common.h"
#include "vec3.h"
#include "ray.h"
#include "color.h"
#include "hittable.h"

color<double> ray_color(ray<double>& r, hittable& obj){
    hit_record res; 
    if(obj.hit(r, interval(0, infinity), res)){
        return 0.5 * (res.normal + color<double>(1,1,1));
    }
    vec3<double> unit_direction = unit_vector(r.direction()); 
    auto a = 0.5*(unit_direction.y()+1.0); 
    return (1.0-a)*color<double>(1.0, 1.0, 1.0) + a*color<double>(0.5, 0.7, 1.0);
}

class Camera {
    public:
        // data members 
        double image_width = 800;
        double aspect_ratio = 9.0/16.0; 
        double viewport_height = 2.0;
        double focal_length = 1.0; 
        point3<double> camera_center = point3<double>(0,0,0); 

    private:
        double image_height, viewport_width;
        vec3<double> viewport_u, viewport_v, pixel_delta_u, pixel_delta_v; 
        point3<double> viewport_center, viewport_upper_left, pixel00_loc; 
        // member functions
        void compute_image_height(){
            image_height = static_cast<int>(image_width*aspect_ratio); 
            image_height =(image_height<1)? 1:image_height;
        }
        void compute_viewport(){
            viewport_width = viewport_height * static_cast<double>(image_width/image_height);
            viewport_u = vec3<double>(viewport_width, 0, 0); 
            viewport_v = vec3<double>(0, -viewport_height, 0);
            pixel_delta_u = viewport_u/static_cast<double>(image_width);
            pixel_delta_v = viewport_v/static_cast<double>(image_height);
            viewport_center = camera_center + vec3<double>(0, 0, focal_length);
            viewport_upper_left = camera_center
                - vec3<double>(0, 0, focal_length) - viewport_u/2.0 - viewport_v/2.0;
            pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
        }

    public:
        // constructor
        Camera() {
            compute_image_height(); 
            compute_viewport(); 
        }
        // Render
        void render(hittable& world) {
            std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";
            for (int j = 0; j < image_height; ++j) {
                for (int i = 0; i < image_width; ++i) {
                    // std::cout << v << std::endl; 
                    auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
                    auto ray_direction = pixel_center - camera_center;
                    ray ray_(camera_center, ray_direction);
                    color<double> pixel_color = ray_color(ray_, world);
                    write_color(std::cout, pixel_color);
                }
            }

        }

}; 