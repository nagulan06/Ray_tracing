#include <iostream>
#include <cmath>
#include "vec3.h"
#include "utility.h"

double vec3::x() const { return m_coord[0]; }
double vec3::y() const { return m_coord[1]; }
double vec3::z() const { return m_coord[2]; }

double vec3::length() const
{
    double squared = m_coord[0] * m_coord[0] + m_coord[1] * m_coord[1] + m_coord[2] * m_coord[2];
    return sqrt(squared);
}

double vec3::operator [] (int index) const
{
    return m_coord[index];
}
double& vec3::operator [] (int index)
{
    return m_coord[index];
}

vec3& vec3::operator - ()
{
    m_coord[0] = -m_coord[0];
    m_coord[1] = -m_coord[1];
    m_coord[2] = -m_coord[2];

    return *this;
}

vec3 vec3::operator - () const
{
    double x = -m_coord[0];
    double y = -m_coord[1];
    double z = -m_coord[2];

    return vec3(x, y, z);
}

vec3 operator + (const vec3& lhs, const vec3& rhs)
{
    double x = lhs.x() + rhs.x();
    double y = lhs.y() + rhs.y();
    double z = lhs.z() + rhs.z();

    return vec3(x, y, z);
}
vec3 operator - (const vec3& lhs, const vec3& rhs)
{
    double x = lhs.x() - rhs.x();
    double y = lhs.y() - rhs.y();
    double z = lhs.z() - rhs.z();

    return vec3(x, y, z);
}
vec3 operator / (const vec3& lhs, const vec3& rhs)
{
    double x = lhs.x() / rhs.x();
    double y = lhs.y() / rhs.y();
    double z = lhs.z() / rhs.z();

    return vec3(x, y, z);
}
vec3 operator * (const vec3& lhs, const vec3& rhs)
{
    double x = lhs.x() * rhs.x();
    double y = lhs.y() * rhs.y();
    double z = lhs.z() * rhs.z();

    return vec3(x, y, z);
}


vec3 operator * (double s, const vec3& v)
{
    double x = v.x() * s;
    double y = v.y() * s;
    double z = v.z() * s;

    return vec3(x, y, z);
}
vec3 operator * (const vec3& v , double s)
{
    double x = v.x() * s;
    double y = v.y() * s;
    double z = v.z() * s;

    return vec3(x, y, z);
}
vec3 operator / (const vec3& v, double s)
{
    double x = v.x() / s;
    double y = v.y() / s;
    double z = v.z() / s;

    return vec3(x, y, z);
}

vec3& vec3::operator += (const vec3& rhs)
{
    this->m_coord[0] += rhs.m_coord[0];
    this->m_coord[1] += rhs.m_coord[1];
    this->m_coord[2] += rhs.m_coord[2];

    return *this;
}
vec3& vec3::operator -= (const vec3& rhs)
{
    this->m_coord[0] -= rhs.m_coord[0];
    this->m_coord[1] -= rhs.m_coord[1];
    this->m_coord[2] -= rhs.m_coord[2];

    return *this;
}
vec3& vec3::operator *= (const vec3& rhs)
{
    this->m_coord[0] *= rhs.m_coord[0];
    this->m_coord[1] *= rhs.m_coord[1];
    this->m_coord[2] *= rhs.m_coord[2];

    return *this;
}
vec3& vec3::operator /= (const vec3& rhs)
{
    this->m_coord[0] /= rhs.m_coord[0];
    this->m_coord[1] /= rhs.m_coord[1];
    this->m_coord[2] /= rhs.m_coord[2];

    return *this;
}

std::ostream& operator << (std::ostream& out, const vec3& obj)
{
    return (out << "x: " << obj.x() << " y: " << obj.y() << " z: " << obj.z() << std::endl);
}

void vec3::print()
{
    std::cout << this->x() << " " << this->y() << " " << this->z() << std::endl;
}

double dot(const vec3& u, const vec3& v)
{
    double x = u.x() * v.x();
    double y = u.y() * v.y();
    double z = u.z() * v.z();

    return (x+y+z);
}

vec3 cross(const vec3& u, const vec3& v)
{
    double x = u.y() * v.z() - u.z() * v.y();
    double y = u.z() * v.x() - u.x() * v.z();
    double z = u.x() * v.y() - u.y() * v.x();

    return vec3(x,y,z);
}

vec3 unit(const vec3& vec)
{
    return vec / vec.length();
}

vec3 vec3::random()
{
    return vec3(random_double(), random_double(), random_double());
}

vec3 vec3::random(double min, double max)
{
    return vec3(random_double(min, max), random_double(min,max), random_double(min,max));
}

vec3 random_in_unit_sphere()
{
    vec3 rand = vec3::random(-1, 1);
    while (1)
    {
        if (rand.length() > 1)
            continue;
        return rand;
    }
}

#warning TODO: try a simple method
vec3 random_unit_vector()
{
    // Cylindrical coordinates - r, theta, z
    // x^2 + y^2 = r^2 ; 0 <= theta <= 2*pi
    // x = r*cos(theta),  y = r*sin(theta),  z as it is in cartesian  
    double theta = random_double(0, 2 * pi);
    double z = random_double(-1, 1);
    double r = sqrt(1 - z * z);

    return vec3(r * cos(theta), r * sin(theta), z);
}