#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray
{
	point3 m_origin;
	vec3 m_direction;
public:
	ray() {}
	// Intitialize origin and direction of the ray
	ray(const point3& orig, const vec3& dir) : m_origin(orig), m_direction(dir) {}

	// Functions that return origin and direction of ray as rvalue
	point3 origin() const { return m_origin;  }
	vec3 direction() const { return m_direction; }

	// Functions that return origin and direction of ray as lvalue
	point3& origin() { return m_origin; }
	vec3& direction() { return m_direction; }

	// Function to calculate position (point3) along the ray for a particular ray parameter (t)
	point3 at(double t) const { return (m_origin + (t * m_direction)); }
};

#endif 