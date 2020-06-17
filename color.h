#ifndef COLOR_H
#define COLOR_H

#include <iostream>

#include "vec3.h"
#include "utility.h"

// Convert the pixel value to a range [0,255] and print it in the PPM format.
inline void write_color(std::ostream& out, const color& pixel, int num_samples)
{
	double r = pixel.x() / num_samples;
	double g = pixel.y() / num_samples;
	double b = pixel.z() / num_samples;

	// r, g, and b values are translated to [0, 255]
	out << static_cast <int> (clamp(r, 0.0, 0.999) * 256) << ' '
		<< static_cast <int> (clamp(g, 0.0, 0.999) * 256) << ' '
		<< static_cast <int> (clamp(b, 0.0, 0.999) * 256) << "\n";
}

#endif

