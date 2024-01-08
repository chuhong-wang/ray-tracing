#pragma once
#include <iostream>

#include "vec3.h"

template <typename T>
using Color = Vec3<T>;

template <typename T>
void write_color(std::ostream &out, Color<T> pixel_color) {
  // Write the translated [0,255] value of each color component.
  out << static_cast<int>(255.999 * pixel_color.x()) << ' '
      << static_cast<int>(255.999 * pixel_color.y()) << ' '
      << static_cast<int>(255.999 * pixel_color.z()) << '\n';
}
