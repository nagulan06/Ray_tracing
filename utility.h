#ifndef UTILITY_H
#define UTILITY_H

#include <limits>
#include <random>

// constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// functions
inline double degrees_to_radians(double degrees)
{
	return degrees * pi / 180;
}

// Generates a random double value
inline double random_double(double min = 0.0, double max = 1.0)
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	static std::uniform_real_distribution<double> dis(min, max);
	
	return dis(gen);
}

// Clamp
inline double clamp(double val, double min, double max)
{
	if (val < min)
		return min;
	if (val > max)
		return max;
	return val;
}

inline void init_ppm(int image_width, int image_height, int max_color)
{
	// PPM image format. Rows and columns. Max color value.
	std::cout << "P3\n"
		<< image_width << " " << image_height
		<< std::endl << max_color << std::endl;
}

#endif