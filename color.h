#ifndef COLOR_H
#define COLOR_H

#include <iostream>
#include "ray.h"
#include "hittable.h"
#include "vec3.h"

color diffuse_color(const ray& , const hittable_list& , int );

color ray_color(const ray&, const hittable_list&, int);

color nomral_color(const ray&, const hittable_list&);

void write_color(std::ostream& , const color& , int );

#endif

