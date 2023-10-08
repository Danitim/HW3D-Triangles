#include "../geometry/geometry.hpp"
#include "../geometry/algorithm.hpp"

bool segpnt_intersection3D(const LineSeg3D &ls, const Point3D &p);

bool segseg_intersection3D(const LineSeg3D &ls0, const LineSeg3D &ls1);

bool tripnt_intersection3D(const Triangle3D &t, const Point3D &p);

bool triseg_intersection3D(const Triangle3D &t, const LineSeg3D &ls);