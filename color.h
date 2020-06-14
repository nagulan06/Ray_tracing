#ifndef COLOR_H
#define COLOR_H

#include <iostream>
#include "vec3.h"

// Convert the pixel value to a range [0,255] and print it in the PPM format.
inline void write_color(std::ostream& out, const color& pixel)
{
	out << static_cast <int> (pixel.x() * 255.999) << ' '
		<< static_cast <int> (pixel.y() * 255.999) << ' '
		<< static_cast <int> (pixel.z() * 255.999) << "\n";
}

#endif

