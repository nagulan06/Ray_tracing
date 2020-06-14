#include <iostream>
#include <algorithm>
#include <cmath>
#include "vec3.h"
#include "color.h"
#include "ray.h"

double intersect(const ray& r, const point3& centre, double radius)
{
	point3 oc = r.origin() - centre;			// (A-C)
	double a = dot(r.direction(), r.direction());
	double b = 2.0 * dot(r.direction(), oc);
	double c = dot(oc, oc) - radius * radius;

	double discriminant = b * b - 4 * a * c;
	
	// If the ray intersects with the sphere.
	if (discriminant >= 0)
	{
		// calculate the closest intersection point
		double root = (-b - sqrt(b * b - 4 * a * c)) / (2 * a);
		return root;
	}
	return -1.0;
}

color ray_color(const ray& r, int &ball_count, int &blue_count)
{
	vec3 unit_vec = unit(r.direction());
	// t lies between 0 and 1 and it is scaled based on the 'y' value of the unit vector
	double t = (unit_vec.y() + 1.0) * 0.5;

	// centre and radius of circle
	point3 centre(0, 0, -1);
	double radius = 0.5;
	double root = intersect(r, centre, radius);
	if (root >= 0.0)
	{
		ball_count += 1;
		// Find intersection point (p), and hence find unit normal vector ( p - c )
		// Find a scaled value depending on the normal vector.
		point3 intersection_point = r.at(root);
		vec3 normal_vec = unit(intersection_point - vec3(0, 0, -1));
		double scale_val = std::max(0.0, dot(-(r.direction()), normal_vec));

		return color(1, scale_val * 0.5, scale_val * 0.5);
		//return 0.5 * color(normal_vec.x()+1, normal_vec.y()+1, normal_vec.z()+1);
	}
	else
	{
		blue_count += 1;
		// calculate the pixel value using lerp - Between blue and white. 
		color pixel = (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
		return pixel;
	}
}

int main()
{
	// Image dimension
	const int image_width = 384;
	const double aspect_ratio = 16.0 / 9.0;
	const int image_height = static_cast<int> (image_width / aspect_ratio);

	// viewport dimensions
	double viewport_height = 2;
	double focal_length = 1;
	double viewport_width = viewport_height * aspect_ratio;
	vec3 horizontal(viewport_width, 0, 0);
	vec3 vertical(0, viewport_height, 0);
	point3 origin(0, 0, 0);
	point3 lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);

	// Generate image pixels bases on the viewport vectors
	// PPM image format. Rows and columns. Max color value.
	std::cout << "P3\n"
		<< image_width << " " << image_height
		<< "\n255\n";
	// RGB triplets
	int ball_count = 0;
	int blue_count = 0;
	for (int i = image_height - 1; i >= 0; --i)
	{
		std::cerr << "\r Lines remaining: " << i << std::flush;
		for (int j = 0; j < image_width; ++j)
		{
			double u = (double)i / (image_height - 1);
			double v = (double)j / (image_width - 1);

			ray r(origin, lower_left_corner + u * vertical + v * horizontal - origin);
			color pixel = ray_color(r, ball_count, blue_count);
			write_color(std::cout, pixel);
		}
	}
	std::cerr << "\nDone...\n";
	std::cerr << "Ball count = " << ball_count << " "
		<< "Blue count = " << blue_count << std::endl;
	return 0;
}