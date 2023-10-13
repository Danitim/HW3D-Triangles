#pragma once
#include <set>
#include "geometry/geometry3D.hpp"

void intersect_each_each(std::set<int>& intersections, std::vector<Geo3D::Triangle>& triangles);