#include "geometry2D.hpp"
#include <cmath>
#include <vector>


namespace Geo3D {
class Vector {
    float x, y, z;
public:
    Vector() : x(0.0f), y(0.0f), z(0.0f) {}
    Vector(float x, float y, float z) : x(x), y(y), z(z) {}

    float getX() const {return x;}
    float getY() const {return y;}
    float getZ() const {return z;}

    Vector operator+(const Vector& v) const {return Vector(x + v.x, y + v.y, z + v.z);}
    Vector operator-(const Vector& v) const {return Vector(x - v.x, y - v.y, z - v.z);}
    bool operator==(const Vector& v) const {return fabs(x-v.x) < cnst::EPS && fabs(y-v.y) < cnst::EPS && fabs(z-v.z) < cnst::EPS;}
    bool operator!=(const Vector& v) const {return !(*this == v);}

    float dot(const Vector& v) const {return x * v.x + y * v.y + z * v.z; }
    Vector cross(const Vector& v) const {return Vector(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);}

    short max_component() const {return (x > y) ? ((x > z) ? 0 : 2) : ((y > z) ? 1 : 2);}
    bool collinear(const Vector& v) const {return ((*this).cross(v)) == Vector();}

    void print() const {std::cout << "3D Vector: " << "(" << x << ", " << y << ", " << z << ")" << std::endl;}
};

class Point {
    float x, y, z;
public:
    Point() : x(0.0f), y(0.0f), z(0.0f) {}
    Point(float x, float y, float z) : x(x), y(y), z(z) {}

    float getX() const {return x;}
    float getY() const {return y;}
    float getZ() const {return z;}

    Geo2D::Point to_point2D(short axis_index) const;
    Vector to_vector() const {return Vector(x, y, z);}

    float operator==(const Point& p) const {return fabs(x - p.x) < cnst::EPS && fabs(y - p.y) < cnst::EPS && fabs(z - p.z) < cnst::EPS;}
    float operator!=(const Point& p) const {return !(*this == p);}
    Vector operator-(const Point& p) const {return Vector(x - p.x, y - p.y, z - p.z);}
    Vector operator-(const Point& p) {return Vector(x - p.x, y - p.y, z - p.z);}

    void print() const {std::cout << "3D Point: " << "(" << x << ", " << y << ", " << z << ")" << std::endl;}
};

class Line {
    Point p;
    Vector d;
public:
    Line() : p(Point()), d(Vector()) {}
    Line(Point p, Vector d) : p(p), d(d) {}

    Point getP() const {return p;}
    Vector getD() const {return d;}

    void print() const;
};

class LineSeg {
    Point p1, p2;
public:
    LineSeg() : p1(Point()), p2(Point()) {}
    LineSeg(Point p1, Point p2) : p1(p1), p2(p2) {}

    Point getP1() const {return p1;}
    Point getP2() const {return p2;}

    Geo2D::LineSeg to_lineseg2D(short axis_index) const;

    Vector getDirection() const {return p2 - p1;}

    bool intersect(const Point& p) const;
    bool intersect(const LineSeg& ls) const;

    void print() const;
};

class Plane {
    Vector n;
    float d;
public:
    Plane() : n(Vector()), d(0.0f) {}
    Plane(float a, float b, float c, float d) : n(Vector(a, b, c)), d(d) {}
    Plane(Vector n, float d) : n(n), d(d) {}

    Vector getNormal() const {return n;}
    float getD() const {return d;}

    Line intersection(const Plane& other) const;

    bool coplanar(const Plane& ohter) const;
    bool equal(const Plane& other) const;

    void print() const;
};

class Triangle {
    Point p1, p2, p3;
    short type;
public:
    Triangle() : p1(Point()), p2(Point()), p3(Point()) {type = get_type();}
    Triangle(Point p1, Point p2, Point p3) : p1(p1), p2(p2), p3(p3) {type = get_type();}

    //Degenerate cases:
    Point to_point() const;
    LineSeg to_lineseg() const;

    //Not so degenerate cases:
    Geo2D::Triangle to_triangle2D(short axis_index) const;

    Point getP1() const {return p1;}
    Point getP2() const {return p2;}
    Point getP3() const {return p3;}

    short get_type() const;
    Triangle rearrangeVertices(std::vector<float> &sign_dist) const;
    std::vector<float> intersection_interval(const std::vector<float> sign_dist, Point line_p, Vector line_d) const;
    bool equal(const Triangle &t) const;

    Plane get_plane() const;
    std::vector<float> signed_distances(const Vector &n, float d) const;

    bool intersect(const Point& p) const;
    bool intersect(const LineSeg& ls) const;
    bool intersect(const Triangle& t) const;

    void print() const;
};
}