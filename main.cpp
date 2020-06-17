#include <iostream>
#include <algorithm>
#include <cmath>
#include <memory>
#include <limits>

#include "utility.h"
#include "vec3.h"
#include "color.h"
#include "ray.h"
#include "hittable.h"
#include "camera.h"


color ray_color(const ray& r, const hittable_list& world_list)
{
	vec3 unit_vec = unit(r.direction());
	// t lies between 0 and 1 and it is scaled based on the 'y' value of the unit vector
	double bg_scale = (unit_vec.y() + 1.0) * 0.5;

	hit_record rec;
	double t_min = 0;
	double t_max = infinity;
	bool intersect = world_list.hit(r, t_min, t_max, rec);
	
	if (intersect)
	{
		// return pixel color with respect to the unit normal vector
		vec3 normal_vec = rec.normal;
		
		/*
		double scale_val = std::max(0.0, dot(-(r.direction()), normal_vec));
		return color(1, scale_val * 0.5, scale_val * 0.5);
		*/
		
		return 0.5 * color(normal_vec.x() + 1, normal_vec.y() + 1, normal_vec.z() + 1);
	}
	else
	{
		// If not hit, return the pixel color for the background
		// calculate the pixel value using lerp - Between blue and white. 
		color pixel = (1.0 - bg_scale) * color(1.0, 1.0, 1.0) + bg_scale * color(0.5, 0.7, 1.0);
		return pixel;
	}
}

int main()
{
	// Image dimension
	const int image_width = 384;
	const double aspect_ratio = 16.0 / 9.0;
	const int image_height = static_cast<int> (image_width / aspect_ratio);

	// Set value for Number of samples per pixel - This is used for antialiasing
	const int num_samples = 100;

	// Setup camera
	camera cam;

	// Add two spheres to the hittable list
	std::shared_ptr<hittable> small = std::make_shared<sphere>(point3(0, 0, -1), 0.5);
	std::shared_ptr<hittable> ground = std::make_shared<sphere>(point3(0, -100.5, -1), 100);
	hittable_list world_list;
	world_list.clear();
	// The order in which objects are pushed into the vector matters when they overlap
	// The last pushed object can overlap all those previously pushed.
	world_list.add(ground);
	world_list.add(small);
	
	// Initialize a ppm image with max color value of 255.
	init_ppm(image_width, image_height, 255);
	// Generate image pixels based on the viewport vectors
	// RGB triplets
	for (int i = image_height - 1; i >= 0; --i)
	{
		std::cerr << "\r Lines remaining: " << i << std::flush;
		for (int j = 0; j < image_width; ++j)
		{
			color pixel;
			for (int s = 0; s < num_samples; ++s)
			{
				double ver = ((double)i + random_double()) / (image_height - 1);
				double hor = ((double)j + random_double()) / (image_width - 1);

				ray r = cam.get_ray(hor, ver);
				pixel += ray_color(r, world_list);
			}
			write_color(std::cout, pixel, num_samples);
		}
	}
	std::cerr << "\n DONE ..." << std::endl;
	
	return 0;
}