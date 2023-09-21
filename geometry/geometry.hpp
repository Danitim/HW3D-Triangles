#pragma once

#include <iostream>
#include <iomanip>
#include <vector>
#include <set>
#include <numeric>
#include <algorithm>
#include <cmath>

class Point3D;
class Point2D;
class Triangle3D;
class Triangle2D;
class Plane3D;
class Line3D;


//Point-type classes
class Point2D {
    float x, y;

public:
    Point2D(float x, float y);
    Point2D(const Point3D &p, short axis_index);

    void operator=(Point2D &other);
    Point2D operator+(Point2D &other);
    Point2D operator-(Point2D &other);

    void print() const;
    bool equal(const Point2D &a) const;

    friend class Point3D;
    friend class Triangle2D;
    friend float cross(const Point2D &a, const Point2D &b);
    friend bool check_intersection2D(const Triangle2D &t1, const Triangle2D &t2);
    friend bool edges_intersect(const Point2D &p1, const Point2D &q1, const Point2D &p2, const Point2D &q2);
};

class Point3D {
    float x, y, z;

public:
    Point3D();
    Point3D(float x, float y, float z);

    void operator=(Point3D &other);
    Point3D operator+(Point3D &other);
    Point3D operator-(Point3D &other);

    bool collinear(const Point3D &p) const;
    void print() const;
    bool equal(const Point3D &a) const;

    friend class Point2D;
    friend class Triangle2D;
    friend class Triangle3D;
    friend class Line3D;
    friend class Plane3D;
    friend std::istream& operator>>(std::istream &input, Point3D &a);
    friend float dot(const Point3D &a, const Point3D &b);
    friend void cross(Point3D &prod, const Point3D &a, const Point3D &b);
    friend float dist3D(const Point3D &p1, const Point3D &p2);
};


//Triangle-type classes
class Triangle2D {
    std::vector<Point2D> vertices;

public:
    Triangle2D(const Point2D &v0, const Point2D &v1, const Point2D &v2);
    Triangle2D(const Triangle3D &t, short axis_index);

    bool has_inside(const Point2D &p) const;
    void print() const;
    bool equal(const Triangle2D &t) const;
    bool valid() const;

    friend class Triangle3D;
    friend bool check_intersection2D(const Triangle2D &t1, const Triangle2D &t2);
};

class Triangle3D {
    std::vector<Point3D> vertices;

public:
    Triangle3D(const Point3D &v0, const Point3D &v1, const Point3D &v2);

    void copy_and_rearrange(std::vector<Point3D> &v, const std::vector<float> &sign_dist) const;
    void print() const;
    bool equal(const Triangle3D &t) const;
    bool valid() const;

    friend class Plane3D;
    friend class Triangle2D;
    friend void signed_distances(std::vector<float> &signdist, const Triangle3D &t, const Plane3D &p);
};


//Plane class
class Plane3D {
    Point3D n;
    float d;

public:
    Plane3D(float a, float b, float c, float d);
    Plane3D(const Triangle3D &t);

    short nearly_oriented_axis();
    void print() const;
    bool coplanar(const Plane3D &p);
    bool equal(const Plane3D &p);

    friend class Line3D;
    friend void signed_distances(std::vector<float> &signdist, const Triangle3D &t, const Plane3D &p);
};


//Line class
class Line3D {
    Point3D p;
    Point3D d;

public:
    Line3D(const Point3D &p, const Point3D &d);
    Line3D(const Plane3D &p0, const Plane3D &p1);

    bool equal(const Line3D &l) const;
    void print() const;

    friend void intersection_interval(std::vector<float> &interval, std::vector<Point3D> &v, std::vector<float> signdist, Line3D &l);
};


//Other geometric functions
bool same_sign(float a, float b);

float dot(const Point3D &a, const Point3D &b);
void cross(Point3D &prod, const Point3D &a, const Point3D &b);
float cross(const Point2D &a, const Point2D &b);

float dist3D(const Point3D &p1, const Point3D &p2);

void signed_distances(std::vector<float> &signdist, const Triangle3D &t, const Plane3D &p);

void intersection_interval(std::vector<float> &interval, std::vector<Point3D> &v, std::vector<float> signdist, Line3D &l);

bool check_intersection2D(const Triangle2D &t1, const Triangle2D &t2);

bool edges_intersect(const Point2D &p1, const Point2D &q1, const Point2D &p2, const Point2D &q2);