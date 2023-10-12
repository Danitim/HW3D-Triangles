#include <iostream>
#include <cmath>

namespace cnst {
    const float EPS = 0.001;
}

class Vector2D {
    float x, y;
public:
    Vector2D() : x(0.0f), y(0.0f) {}
    Vector2D(float x, float y) : x(x), y(y) {}

    float getX() const { return x; }
    float getY() const { return y; }

    bool operator==(const Vector2D& other) const { return fabs(x - other.x) <= cnst::EPS && fabs(y - other.y) <= cnst::EPS; }
    bool operator!=(const Vector2D& other) const { return !(*this == other); }

    Vector2D operator+(const Vector2D& other) const { return Vector2D(x + other.x, y + other.y); }
    Vector2D operator-(const Vector2D& other) const { return Vector2D(x - other.x, y - other.y); }

    float dot(const Vector2D& other) const { return x * other.x + y * other.y; }
    float cross(const Vector2D& other) const { return x * other.y - y * other.x; }

    float length() const { return std::sqrt(x * x + y * y); }
    Vector2D normalize() const { return Vector2D(x / length(), y / length()); }

    void print() const { std::cout << "Vector2D: " << "(" << x << ", " << y << ")" << std::endl; }
};


class Point2D {
    float x, y;
public:
    Point2D() : x(0.0f), y(0.0f) {}
    Point2D(float x, float y) : x(x), y(y) {}

    float getX() const { return x; }
    float getY() const { return y; }

    bool operator==(const Point2D& other) const { return fabs(x - other.x) <= cnst::EPS && fabs(y - other.y) <= cnst::EPS; }
    bool operator!=(const Point2D& other) const { return !(*this == other); }

    //Method that converts a difference between two points to a vector
    Vector2D operator-(const Point2D& other) const { return Vector2D(x - other.x, y - other.y); }
    Vector2D operator-(const Point2D& other) { return Vector2D(x - other.x, y - other.y); }

    void print() const { std::cout << "Point2D: " << "(" << x << ", " << y << ")" << std::endl; }
};


class LineSeg2D {
    Point2D p1, p2;
public:
    LineSeg2D() : p1(Point2D()), p2(Point2D()) {}
    LineSeg2D(Point2D p1, Point2D p2) : p1(p1), p2(p2) {}

    Point2D getP1() const { return p1; }
    Point2D getP2() const { return p2; }

    Vector2D getDirection() const { return p2 - p1; }
    float length() const { return getDirection().length(); }

    bool operator==(const LineSeg2D& other) const;
    bool operator!=(const LineSeg2D& other) const { return !(*this == other); }

    bool intersect(const LineSeg2D& other) const;

    void print() const;
};


class Triangle2D {
    Point2D p1, p2, p3;
public:
    Triangle2D() : p1(Point2D()), p2(Point2D()), p3(Point2D()) {}
    Triangle2D(Point2D p1, Point2D p2, Point2D p3) : p1(p1), p2(p2), p3(p3) {}

    Point2D getP1() const { return p1; }
    Point2D getP2() const { return p2; }
    Point2D getP3() const { return p3; }

    LineSeg2D getEdge1() const { return LineSeg2D(p1, p2); }
    LineSeg2D getEdge2() const { return LineSeg2D(p2, p3); }
    LineSeg2D getEdge3() const { return LineSeg2D(p3, p1); }

    bool operator==(const Triangle2D& other) const;
    bool operator!=(const Triangle2D& other) const { return !(*this == other); }

    bool has_inside(const Point2D& p) const;
    bool intersect(const LineSeg2D& ls) const;
    bool intersect(const Triangle2D& t) const;

    void print() const;
};


