#ifndef UTILITY_H
#define UTILITY_H

#include <limits>

// constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// functions
inline double degrees_to_radians(double degrees)
{
	return degrees * pi / 180;
}

#endif