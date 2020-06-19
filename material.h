#ifndef MATERIAL_H
#define MATERIAL_H

#include "ray.h"
#include "vec3.h"
#include "hittable.h"


class material
{
public:
	virtual bool scatter(
		const ray& ray_in, hit_record& rec, color& attenuation, ray& scattered
	) const = 0;
};

class lambertian : public material
{
	color albedo;
public:
	lambertian(color a) : albedo(a) {}

	bool scatter(
		const ray& ray_in, hit_record& rec, color& attenuation, ray& scattered
	) const override
	{
		point3 point_on_unit_circle = rec.hit_point + rec.normal + random_in_hemisphere(rec.normal);
		scattered = ray(rec.hit_point, point_on_unit_circle - rec.hit_point);
		attenuation = albedo;
		
		return true;
	}
};

class metal : public material
{
	color albedo;
public:
	metal(color a) : albedo(a) {}
	bool scatter(
		const ray& ray_in, hit_record& rec, color& attenuation, ray& scattered
	) const override
	{
		vec3 reflect_dir = reflect(unit(ray_in.direction()), rec.normal);
		scattered = ray(rec.hit_point, reflect_dir);
		attenuation = albedo;

		return (dot(reflect_dir, rec.normal) > 0);
	}
};
#endif