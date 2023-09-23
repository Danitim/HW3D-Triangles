#pragma once
#include "../geometry/geometry.hpp"
#include "degenerate.hpp"

void intersect_each_with_each(std::set<int> &intersections, const std::vector<Triangle3D> &arrayy);

bool typed_intersection(const Triangle3D &t0, const Triangle3D &t1);

bool tritri_intersection3D(const Triangle3D &t0, const Triangle3D &t1);