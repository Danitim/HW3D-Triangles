#include "degenerate.hpp"

bool segpnt_intersection3D(const LineSeg3D &ls, const Point3D &p) {
    Vector3D ax = p - ls.p0;
    Vector3D ab = ls.p1 - ls.p0;

    //Check for collinearity
    if (!ax.collinear(ab)) return false;

    float ax_ab = dot(ax, ab);
    return (ax_ab >= 0) && (ax_ab <= dot(ab, ab));
}

static bool proj_intersection(float a1, float a2, float b1, float b2) {
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
    Vector3D v0 = t.vertices[0] - p;
    Vector3D v1 = t.vertices[1] - p;
    Vector3D v2 = t.vertices[2] - p;

    Vector3D n; cross(n, (t.vertices[1]-t.vertices[0]), (t.vertices[2]-t.vertices[0]));
    if (fabs(dot(n, v0)) > cnst::EPS)
        return false;

    float d00 = dot(v0, v0);
    float d01 = dot(v0, v1);
    float d02 = dot(v0, v2);
    float d11 = dot(v1, v1);
    float d12 = dot(v2, v2);

    float d = d00*d11 - d01*d01;
    if (fabs(d) < cnst::EPS) return true;

    float u = (d11*d02 - d01*d12)/d;
    float v = (d00*d12 - d01*d02)/d;
    return (u >= 0) && (v >= 0) && (u + v <= 1);
}

bool triseg_intersection3D(const Triangle3D &t, const LineSeg3D &ls) {
    Vector3D v0 = t.vertices[1] - t.vertices[0];
    Vector3D v1 = t.vertices[2] - t.vertices[0];
    Vector3D d = ls.p1 - ls.p0;

    Vector3D n; cross(n, v0, v1);
    Vector3D h; cross(h, d, v1);
    float a = dot(v0, h);
    if (fabs(a) < cnst::EPS) {
        if (fabs(dot((ls.p0 - t.vertices[0]), n)) > cnst::EPS)
            return false;
        short axis_index = n.nearly_oriented_axis();
        Triangle2D t_2d(t, axis_index);
        LineSeg2D ls_2d(ls, axis_index);
        return triseg_intersection2D(t_2d, ls_2d);
    }

    float f = 1.0/a;
    Vector3D s = ls.p0 - t.vertices[0];
    float u = f*dot(s, h);
    if ((u < 0.0) || (u > 1.0))
        return false;

    Vector3D q; cross(q, s, v0);
    float v = f * dot(d, q);
    if ((v < 0.0) || (u + v > 1.0))
        return false;

    float w = f*dot(v1, q);
    if ((w >= cnst::EPS) && (w <= 1.0 + cnst::EPS))
        return true;
    
    return false;
}
