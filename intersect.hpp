#pragma once
#include "geometry/geometry.hpp"

void find_intersecting_triangles(std::set<int> &intersections, const std::vector<Triangle3D> &arrayy);

bool check_intersection3D(const Triangle3D &t0, const Triangle3D &t1);