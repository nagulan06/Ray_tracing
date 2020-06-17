#ifndef CAMERA_H
#define CAMERA_H

#include "vec3.h"
#include "ray.h"

class camera
{
	// Camera viewport dimensions and related stuff
	double aspect_ratio;
	double viewport_height;
	double focal_length;
	double viewport_width;

	point3 lower_left_corner;
	point3 origin;
	vec3 horizontal;
	vec3 vertical;
public:
	camera()
	{
		aspect_ratio = 16.0 / 9.0;
		viewport_height = 2;
		focal_length = 1;
		viewport_width = viewport_height * aspect_ratio;
		horizontal = { viewport_width, 0, 0 };
		vertical = { 0, viewport_height, 0 };
		origin = { 0,0,0 };
		lower_left_corner = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal_length);
	}

	ray get_ray(double hor, double ver) const
	{
		// ray (origin, direction)
		return ray(origin, lower_left_corner + hor * horizontal + ver * vertical - origin);
	}
};

#endif