#include "geometry.hpp"

void signed_distances(std::vector<float> &signdist, const Triangle3D &t, const Plane3D &p);

void intersection_interval(std::vector<float> &interval, std::vector<Point3D> &v, std::vector<float> signdist, Line3D &l);

bool tritri_intersection2D(const Triangle2D &t1, const Triangle2D &t2);

bool triseg_intersection2D(const Triangle2D &t, const LineSeg2D &ls);

bool segseg_intersection2D(const Point2D &p1, const Point2D &q1, const Point2D &p2, const Point2D &q2);