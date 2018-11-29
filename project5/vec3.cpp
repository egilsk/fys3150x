#include "vec3.h"

vec3::vec3()
{
    // Uncomment to see what methods is called when!
//    cout << "Using default constructor" << endl;
    v[0] = 0;
    v[1] = 0;
    v[2] = 0;
}


vec3::vec3(double x, double y, double z)
{
    // Uncomment to see what methods is called when!
//    cout << "Using parametrized constructor" << endl;
    v[0] = x;
    v[1] = y;
    v[2] = z;
}

vec3::~vec3()
{
    // Uncomment to see what methods is called when!
//    cout << "Using destructor" << endl;
}

vec3::vec3(vec3 const &copy)
{
    // Uncomment to see what methods is called when!
//    cout << "Using copy constructor" << endl;
    v[0] = copy.v[0];
    v[1] = copy.v[1];
    v[2] = copy.v[2];
}

vec3 &vec3::operator= (const vec3 &copy) {
//    cout << "Using copy assignemnt" << endl;
    v[0] = copy.v[0];
    v[1] = copy.v[1];
    v[2] = copy.v[2];
    return *this;
}

void vec3::print()
{
    cout << "[" << v[0] << ", " << v[1] << ", " << v[2] << "]" << endl;
}

void vec3::print(string msg)
{
    cout << msg;
    print();
}

vec3 vec3::cross(vec3 other)
{
    return vec3(v[1]*other.z() - v[2]*other.y(), v[2]*other.x() - v[0]*other.z(), v[0]*other.y() - v[1]*other.x());
}

double vec3::dot(vec3 other)
{
    return other[0]*v[0] + other[1]*v[1] + other[2]*v[2];
}


double vec3::length() const
{
    return sqrt(lengthSquared());
}

double vec3::lengthSquared() const
{
    return v[0]*v[0] + v[1]*v[1] + v[2]*v[2];
}

vec3 &vec3::operator+=(const vec3 &other)
{
    v[0] += other.v[0];
    v[1] += other.v[1];
    v[2] += other.v[2];
    return *this;
}

vec3 &vec3::operator-=(const vec3 &other)
{
    v[0] -= other.v[0];
    v[1] -= other.v[1];
    v[2] -= other.v[2];
    return *this;
}

vec3 &vec3::operator*=(const double &other)
{
    v[0] *= other;
    v[1] *= other;
    v[2] *= other;
    return *this;
}

vec3 &vec3::operator/=(const double &other)
{
    v[0] /= other;
    v[1] /= other;
    v[2] /= other;
    return *this;
}
