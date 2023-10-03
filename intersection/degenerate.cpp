#include "degenerate.hpp"

bool segpnt_intersection3D(const LineSeg3D &ls, const Point3D &p) {
    Vector3D ax = p - ls.p0;
    Vector3D ab = ls.p1 - ls.p0;

    //Check for collinearity
    if (!ax.collinear(ab)) return false;

    float ax_ab = dot(ax, ab);
    return (ax_ab >= 0) && (ax_ab <= dot(ab, ab));
}

bool segseg_intersection3D(const LineSeg3D &ls0, const LineSeg3D &ls1) {
    return false;
}

bool tripnt_intersection3D(const Triangle3D &t, const Point3D &p) {
    return false;
}

bool triseg_intersection3D(const Triangle3D &t0, const LineSeg3D &ls) {
    return false;
}
