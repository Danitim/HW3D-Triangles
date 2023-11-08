#include <iostream>
#include <cmath>

namespace cnst {
    const float EPS = 0.001;
}

namespace Geo2D {
class Vector {
    float x, y;
public:
    Vector() : x(0.0f), y(0.0f) {}
    Vector(float x, float y) : x(x), y(y) {}

    float getX() const { return x; }
    float getY() const { return y; }

    bool operator==(const Vector& other) const {return fabs(x - other.x) <= cnst::EPS && fabs(y - other.y) <= cnst::EPS;}
    bool operator!=(const Vector& other) const {return !(*this == other); }
    Vector operator+(const Vector& other) const {return Vector(x + other.x, y + other.y);}
    Vector operator-(const Vector& other) const {return Vector(x - other.x, y - other.y);}

    float dot(const Vector& other) const {return x * other.x + y * other.y;}
    float cross(const Vector& other) const {return x * other.y - y * other.x;}
    float length() const {return std::sqrt(x * x + y * y);}
    Vector normalize() const {int len = length(); return Vector(x/len, y/len);}

    void print() const {std::cout << "2D Vector: " << "(" << x << ", " << y << ")" << std::endl;}
};

class Point {
    float x, y;
public:
    Point() : x(0.0f), y(0.0f) {}
    Point(float x, float y) : x(x), y(y) {}

    float getX() const {return x;}
    float getY() const {return y;}

    bool operator==(const Point& other) const {return fabs(x - other.x) <= cnst::EPS && fabs(y - other.y) <= cnst::EPS;}
    bool operator!=(const Point& other) const {return !(*this == other);}
    Vector operator-(const Point& other) const {return Vector(x - other.x, y - other.y);}
    Vector operator-(const Point& other) {return Vector(x - other.x, y - other.y);}

    void print() const {std::cout << "2D Point: " << "(" << x << ", " << y << ")" << std::endl;}
};

class LineSeg {
    Point p1, p2;
public:
    LineSeg() : p1(Point()), p2(Point()) {}
    LineSeg(Point p1, Point p2) : p1(p1), p2(p2) {}

    Point getP1() const {return p1;}
    Point getP2() const {return p2;}

    Vector getDirection() const {return p2 - p1;}
    float length() const {return getDirection().length();}

    bool operator==(const LineSeg& other) const;
    bool operator!=(const LineSeg& other) const {return !(*this == other);}

    bool intersect(const LineSeg& other) const;

    void print() const;
};

class Triangle {
    Point p1, p2, p3;
public:
    Triangle() : p1(Point()), p2(Point()), p3(Point()) {}
    Triangle(Point p1, Point p2, Point p3) : p1(p1), p2(p2), p3(p3) {}

    Point getP1() const {return p1;}
    Point getP2() const {return p2;}
    Point getP3() const {return p3;}

    LineSeg getEdge1() const {return LineSeg(p1, p2);}
    LineSeg getEdge2() const {return LineSeg(p2, p3);}
    LineSeg getEdge3() const {return LineSeg(p3, p1);}

    bool operator==(const Triangle& other) const;
    bool operator!=(const Triangle& other) const {return !(*this == other);}

    bool has_inside(const Point& p) const;
    bool intersect(const LineSeg& ls) const;
    bool intersect(const Triangle& t) const;

    void print() const;
};
}