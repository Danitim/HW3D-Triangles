#include "degenerate.hpp"

bool segpnt_intersection3D(const LineSeg3D &ls, const Point3D &p) {
    Vector3D ax = p - ls.p0;
    Vector3D ab = ls.p1 - ls.p0;

    //Check for collinearity
    if (!ax.collinear(ab)) return false;

    float ax_ab = dot(ax, ab);
    return (ax_ab >= 0) && (ax_ab <= dot(ab, ab));
}

bool proj_intersection(float a1, float a2, float b1, float b2) {
    if (a1 > a2) std::swap(a1, a2);
    if (b1 > b2) std::swap(b1, b2);
    return std::max(a1, b1) <= std::min(a2, b2);
}

bool segseg_intersection3D(const LineSeg3D &a, const LineSeg3D &b) {
    Vector3D d0 = a.p1 - a.p0;
    Vector3D d1 = b.p1 - b.p0;
    Vector3D x = b.p0 - a.p0;
    Vector3D n; cross(n, d0, d1);

    if (d0.collinear(d1)) {
        if (!d0.collinear(x)) return false;
        return proj_intersection(a.p0.x, a.p1.x, b.p0.x, b.p1.x) &&
                proj_intersection(a.p0.y, a.p1.y, b.p0.y, b.p1.y) &&
                proj_intersection(a.p0.z, a.p1.z, b.p0.z, b.p1.z);
    }
    
    Vector3D v0; cross(v0, d1, x);
    float t0 = dot(v0, n) / dot(n, n);
    if (t0 < 0 || t0 > 1)
        return false;

    Vector3D v1; cross(v1, d0, x);
    float t1 = dot(v1, n) / dot(n, n);
    if (t1 < 0 || t1 > 1)
        return false;
    
    return true;        
}

bool tripnt_intersection3D(const Triangle3D &t, const Point3D &p) {
    return false;
}

bool triseg_intersection3D(const Triangle3D &t0, const LineSeg3D &ls) {
    return false;
}
