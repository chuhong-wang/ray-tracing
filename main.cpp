#include <iostream>
#include "common.h"
#include "vec3.h"
#include "color.h"
#include "ray.h"
#include "sphere.h"

color<double> ray_color(ray<double>& r, hittable& obj){
    hit_record res; 
    if(obj.hit(r, 0, infinity, res)){
        return 0.5*color<double>(res.normal.x()+1, res.normal.y()+1, res.normal.z()+1); // map to R,G,B ⊂ (0,1)
    }
    vec3<double> unit_direction = unit_vector(r.direction()); 
    auto a = 0.5*(unit_direction.y()+1.0); 
    return (1.0-a)*color<double>(1.0, 1.0, 1.0) + a*color<double>(0.5, 0.7, 1.0);
}

int main() {
    // Image and viewport 
    double image_width = 800;
    double aspect_ratio = 9.0/16.0; 
    double image_height = static_cast<int>(image_width*aspect_ratio); 
    image_height =(image_height<1)? 1:image_height; 

    double viewport_height = 2.0; 
    double viewport_width = viewport_height * static_cast<double>(image_width/image_height); 

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    auto viewport_u = vec3<double>(viewport_width, 0, 0); 
    auto viewport_v = vec3<double>(0, -viewport_height, 0);
    auto pixel_delta_u = viewport_u/static_cast<double>(image_width);
    auto pixel_delta_v = viewport_v/static_cast<double>(image_height);

    double focal_length = 1.0; 
    auto camera_center = point3<double>(0,0,0); 
    auto viewport_center = camera_center + vec3<double>(0, 0, focal_length);

    // Calculate the location of the upper left pixel.
    auto viewport_upper_left = camera_center
                             - vec3<double>(0, 0, focal_length) - viewport_u/2.0 - viewport_v/2.0;
    auto pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    // // error checking  
    // std::cout << "viewport " << viewport_width << " " << viewport_height << std::endl; 
    // std::cout << "pixel_delta_u " << pixel_delta_u << "pixel_delta_v " << pixel_delta_v << std::endl;  

    // Render
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; ++j) {
        for (int i = 0; i < image_width; ++i) {
            // std::cout << v << std::endl; 
            auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
            auto ray_direction = pixel_center - camera_center;
            ray r(camera_center, ray_direction);

            Sphere sph(point3<double>(0,0,-1), 0.5); 

            color<double> pixel_color = ray_color(r, sph);
            write_color(std::cout, pixel_color);

        }
    }
}