#pragma once
#include "../geometry/geometry.hpp"

bool segpnt_intersection3D(const Triangle3D &t0, const Triangle3D &t1);

bool segseg_intersection3D(const Triangle3D &t0, const Triangle3D &t1);

bool tripnt_intersection3D(const Triangle3D &t0, const Triangle3D &t1);

bool triseg_intersection3D(const Triangle3D &t0, const Triangle3D &t1);