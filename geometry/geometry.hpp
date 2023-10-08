#pragma once

#include <iostream>
#include <iomanip>
#include <vector>
#include <set>
#include <numeric>
#include <algorithm>
#include <cmath>

namespace cnst {
    const float EPS = 0.001;
}

class Point3D;
class Vector3D;
class Point2D;
class Triangle3D;
class Triangle2D;
class Plane3D;
class Line3D;
class LineSeg3D;
class LineSeg2D;


//Point-type classes
class Point2D {
    float x, y;
public:
    Point2D();
    Point2D(float x, float y);
    Point2D(const Point3D &p, short axis_index);

    void print() const;
    bool equal(const Point2D &a) const;

    friend class Vector2D;
    friend class Point3D;
    friend class Triangle2D;
    friend bool tritri_intersection2D(const Triangle2D &t1, const Triangle2D &t2);
    friend bool edges_intersect(const Point2D &p1, const Point2D &q1, const Point2D &p2, const Point2D &q2);
    friend bool segseg_intersection2D(const Point2D &a1, const Point2D &a2, const Point2D &b1, const Point2D &b2);
};

class Vector2D {
    float x, y;
public:
    Vector2D();
    Vector2D(float x, float y);
    Vector2D(const Point2D &p);

    Vector2D operator+(Vector2D &other);
    Vector2D operator-(Vector2D &other);

    void print() const;
    bool equal(const Vector2D &a) const;

    friend class Point2D;
    friend class Point3D;
    friend class Triangle2D;
    friend float cross(const Vector2D &a, const Vector2D &b);
};

class Point3D {
    float x, y, z;
public:
    Point3D();
    Point3D(float x, float y, float z);
    //Degenerate case
    Point3D(const Triangle3D &t);

    void print() const;
    bool equal(const Point3D &a) const;

    friend class Point2D;
    friend class Vector3D;
    friend class Triangle2D;
    friend class Triangle3D;
    friend class Line3D;
    friend class Plane3D;
    friend Vector3D operator+(const Point3D &a, const Point3D &b);
    friend Vector3D operator-(const Point3D &a, const Point3D &b);
    friend std::istream& operator>>(std::istream &input, Point3D &a);
    friend float dist3D(const Point3D &p1, const Point3D &p2);

    friend bool segseg_intersection3D(const LineSeg3D &ls0, const LineSeg3D &ls1);
    friend bool tripnt_intersection3D(const Triangle3D &t, const Point3D &p);
    friend bool triseg_intersection3D(const Triangle3D &t0, const LineSeg3D &ls);
};


class Vector3D {
    float x, y, z;
public:
    Vector3D();
    Vector3D(float x, float y, float z);
    Vector3D(const Point3D &other);


    short nearly_oriented_axis() const;
    void print() const;
    bool equal(const Vector3D &a) const;
    bool collinear(const Vector3D &p) const;

    friend class Point2D;
    friend class Point3D;
    friend class Triangle2D;
    friend class Triangle3D;
    friend class Line3D;
    friend class Plane3D;
    friend Vector3D operator+(Vector3D &a, Vector3D &b);
    friend Vector3D operator-(Vector3D &a, Vector3D &b);
    friend float dot(const Vector3D &a, const Vector3D &b);
    friend void cross(Vector3D &prod, const Vector3D &a, const Vector3D &b);
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
    friend bool tritri_intersection2D(const Triangle2D &t1, const Triangle2D &t2);
    friend bool triseg_intersection2D(const Triangle2D &t, const LineSeg2D &ls);
};

class Triangle3D {
    std::vector<Point3D> vertices;
    short type = 1; //1 = point, 2 = segment, 3 = triangle
public:
    Triangle3D(const Point3D &v0, const Point3D &v1, const Point3D &v2);

    void copy_and_rearrange(std::vector<Point3D> &v, const std::vector<float> &sign_dist) const;
    Point3D get_vertice(short index) const;
    short get_type() const;
    void print() const;
    bool equal(const Triangle3D &t) const;
    bool valid() const;

    friend class Point3D;
    friend class Plane3D;
    friend class Triangle2D;
    friend class LineSeg3D;
    friend void signed_distances(std::vector<float> &signdist, const Triangle3D &t, const Plane3D &p);\

    friend bool tripnt_intersection3D(const Triangle3D &t, const Point3D &p);
    friend bool triseg_intersection3D(const Triangle3D &t, const LineSeg3D &ls);
};


//Plane class
class Plane3D {
    Vector3D n;
    float d;

public:
    Plane3D(float a, float b, float c, float d);
    Plane3D(const Triangle3D &t);

    short nearly_oriented_axis() const;
    void print() const;
    bool coplanar(const Plane3D &p);
    bool equal(const Plane3D &p);

    friend class Line3D;
    friend void signed_distances(std::vector<float> &signdist, const Triangle3D &t, const Plane3D &p);
};


//Line class
class Line3D {
    Point3D p;
    Vector3D d;

public:
    Line3D(const Point3D &p, const Vector3D &d);
    Line3D(const Plane3D &p0, const Plane3D &p1);

    bool equal(const Line3D &l) const;
    void print() const;

    friend void intersection_interval(std::vector<float> &interval, std::vector<Point3D> &v, std::vector<float> signdist, Line3D &l);
};


//Line segment class
class LineSeg3D {
    Point3D p0;
    Point3D p1;
public:
    LineSeg3D(const Point3D &p0, const Point3D &p1);
    //Degenerate case
    LineSeg3D(const Triangle3D &t);

    bool equal(const LineSeg3D &l) const;
    void print() const;

    friend class LineSeg2D;
    friend bool segpnt_intersection3D(const LineSeg3D &ls, const Point3D &p);
    friend bool segseg_intersection3D(const LineSeg3D &ls0, const LineSeg3D &ls1);
    friend bool triseg_intersection3D(const Triangle3D &t, const LineSeg3D &ls);
};


class LineSeg2D {
    Point2D p0;
    Point2D p1;
public:
    LineSeg2D(const Point2D &p0, const Point2D &p1);
    LineSeg2D(const LineSeg3D &ls, short axis_index);

    bool equal(const LineSeg2D &ls) const;
    void print() const;

    friend bool triseg_intersection2D(const Triangle2D &t, const LineSeg2D &ls);
};


//Other geometric functions
bool same_sign(float a, float b);

float dot(const Vector3D &a, const Vector3D &b);
void cross(Vector3D &prod, const Vector3D &a, const Vector3D &b);
float cross(const Vector2D &a, const Vector2D &b);

float dist3D(const Point3D &p1, const Point3D &p2);