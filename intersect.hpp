#pragma once
#include "geometry/geometry.hpp"

void intersect_each_with_each(std::set<int> &intersections, const std::vector<Triangle3D> &arrayy);

bool typed_intersection(const Triangle3D &t0, const Triangle3D &t1);

bool segpnt_intersection3D(const Triangle3D &t0, const Triangle3D &t1);

bool segseg_intersection3D(const Triangle3D &t0, const Triangle3D &t1);

bool tripnt_intersection3D(const Triangle3D &t0, const Triangle3D &t1);

bool triseg_intersection3D(const Triangle3D &t0, const Triangle3D &t1);

bool tritri_intersection3D(const Triangle3D &t0, const Triangle3D &t1);