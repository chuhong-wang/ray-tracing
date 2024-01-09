#pragma once
#include <iostream>

#include "vec3.h"
#include "interval.h"

template <typename T>
using Color = Vec3<T>;

template <typename T>
void write_color(std::ostream &out, Color<T> pixel_color) {
  // make sure three values in `pixel_color` fall in [0,1]
  static const Interval intensity(0, 0.999); 

  auto r = pixel_color.x(); 
  auto g = pixel_color.y(); 
  auto b = pixel_color.z();  

  // Write the translated [0,255] value of each color component.
  out << static_cast<int>(255.999 * intensity.clamp(r)) << ' '
      << static_cast<int>(255.999 * intensity.clamp(g)) << ' '
      << static_cast<int>(255.999 * intensity.clamp(b)) << '\n';
}
