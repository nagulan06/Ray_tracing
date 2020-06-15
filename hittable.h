#ifndef HITTABLE_H
#define HITTABLE_H

#include <memory>
#include <vector>
#include "vec3.h"
#include "ray.h"

/*
	struct hit_record
	class hittable
	class sphere : hittable
	class hittable_list: hittable
*/

struct hit_record
{
	point3 hit_point;
	double t;
	vec3 normal;
	bool front_face;

	void set_face_normal(const vec3& outward_normal, const ray& r)
	{
		front_face = dot(outward_normal, r.direction()) <= 1;
		normal = front_face ? outward_normal : -outward_normal;
	}
};

// Hittable abstract class
class hittable
{
public:
	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const = 0;
};

// Sphere class derived from hittable. We can add other geometries when needed and derive it from hittable class
class sphere : public hittable
{
	point3 m_centre;
	double m_radius;
public:
	sphere() : m_centre(point3(0, 0, 0)), m_radius(0) {}
	sphere(point3 cen, double radius) : m_centre(cen), m_radius(radius) {}

	// getters
	point3 centre() const { return m_centre; }
	double radius() const { return m_radius; }

	// setters
	void centre(point3 cen) { m_centre = cen; }
	void radius(double rad) { m_radius = rad; }

	// hit sphere
	bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override
	{
		point3 oc = r.origin() - m_centre;			// (A-C)
		double a = dot(r.direction(), r.direction());
		double b = 2.0 * dot(r.direction(), oc);
		double c = dot(oc, oc) - m_radius * m_radius;

		double discriminant = b * b - 4 * a * c;

		// If the ray intersects with the sphere.
		if (discriminant >= 0)
		{
			// calculate the closest intersection point
			double root = (-b - sqrt(b * b - 4 * a * c)) / (2 * a);

			// Find hit point, outward normal and update the hit_record struct
			if (root < t_max && root > t_min)
			{
				rec.hit_point = r.at(root);
				rec.t = root;
				vec3 outward_normal = unit(rec.hit_point - m_centre);
				rec.set_face_normal(outward_normal, r);
				return true;
			}
	
			root = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);
			if (root < t_max && root > t_min)
			{
				rec.hit_point = r.at(root);
				rec.t = root;
				vec3 outward_normal = unit(rec.hit_point - m_centre);
				rec.set_face_normal(outward_normal, r);
				return true;
			}

		}
		return false;
	}
};

// Class to handle list of hittables
class hittable_list : hittable
{
	std::vector < std::shared_ptr<hittable> > m_list;
public:
	void add(std::shared_ptr<hittable> obj)
	{
		m_list.push_back(obj);
	}

	void clear()
	{
		m_list.clear();
	}

	// Iterate through the list of hittables and see if the ray at the current pixel
	// hits any of the hittables.
	bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override
	{
		bool hit_anywhere = false;
		double closest_so_far = t_max;
		hit_record temp_rec;
		for (const auto& obj : m_list)
		{
			if (obj->hit(r, t_min, t_max, rec))
			{
				hit_anywhere = true;
			}
		}
		return hit_anywhere;
	}
};

#endif