#pragma once
#include <iostream>

#include "vec3.h"
#include "interval.h"
#include "common.h"

using Color = Vector;

void write_color(std::ostream &out, Color pixel_color) {
  // make sure three values in `pixel_color` fall in [0,1]
  static const Interval2f intensity(0, 0.999); 

  auto r = pixel_color.x(); 
  auto g = pixel_color.y(); 
  auto b = pixel_color.z();
  gamma_color(r); 
  gamma_color(g); 
  gamma_color(b);   

  // Write the translated [0,255] value of each color component.
  out << static_cast<int>(255.999 * intensity.clamp(r)) << ' '
      << static_cast<int>(255.999 * intensity.clamp(g)) << ' '
      << static_cast<int>(255.999 * intensity.clamp(b)) << '\n';
}
