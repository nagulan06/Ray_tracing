#ifndef VEC3
#define VEC3

class vec3
{
    double m_coord[3];

public:
    vec3(double x = 0, double y = 0, double z = 0) : m_coord{ x,y,z } {}

    double x() const;
    double y() const;
    double z() const;

    // Length/Magnitude of vector
    double length() const;

    // Deferencing vector may appear as both lvalue and rvalue.
    double operator [] (int) const;
    double& operator [] (int);
    // Negate
    vec3& operator - ();
    vec3 operator - () const;

    // Add, Subtract, Multiply and Divide
    vec3& operator += (const vec3&);
    vec3& operator -= (const vec3&);
    vec3& operator *= (const vec3&);
    vec3& operator /= (const vec3&);

    // Print the coordinates of the vector
    void print();

};

// Add, Subtract, Multiply and Divide two vectors
vec3 operator + (const vec3&, const vec3&);
vec3 operator - (const vec3&, const vec3&);
vec3 operator / (const vec3&, const vec3&);
vec3 operator * (const vec3&, const vec3&);

// cout
std::ostream& operator << (std::ostream&, const vec3&);

// Multiply and divide vector by a scalar
vec3 operator * (const vec3&, double);
vec3 operator * (double, const vec3&);
vec3 operator / (const vec3&, double);

// Dot and cross product
double dot(const vec3&, const vec3&);
vec3 cross(const vec3&, const vec3&);

// Unit vector
vec3 unit(const vec3&);

typedef vec3 color;
typedef vec3 point3;    

#endif