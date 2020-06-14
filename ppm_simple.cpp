#include <iostream>
#include "vec3.h"
#include "color.h"
int ppm_simple()
{
	int image_width = 256, image_height = 256;
	// PPM image format. Rows and columns. Max color value.
	std::cout << "P3\n"
		<< image_width << " " << image_height
		<< "\n255\n";
	// RGB triplets
	for (int i = image_height - 1; i >= 0; --i)
	{
		std::cerr << "\rLines remaining: " << i << std::flush;
		for (int j = 0; j < image_width; ++j)
		{
			double r = (double)j / (image_width - 1);
			double g = (double)i / (image_height - 1);
			double b = 0.25;
			write_color(std::cout, color(0.3, 0.7, 1));
		}
	}
	std::cerr << "\nDone..\n";
	return 0;
}