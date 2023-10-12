#include "geometry2D.hpp"

bool LineSeg2D::operator==(const LineSeg2D &other) const {
    return (p1 == other.p1 && p2 == other.p2) ||
           (p1 == other.p2 && p2 == other.p1);
}

bool LineSeg2D::intersect(const LineSeg2D &other) const {
    Vector2D r = getDirection();
    Vector2D s = other.getDirection();
    Vector2D qp = other.getP1() - p1;

    float rxs = r.cross(s);
    float qpxr = qp.cross(r);

    if (rxs == 0) {
        if (qpxr == 0) {
            // Lines are collinear
            float t0 = qp.dot(r) / r.dot(r);
            float t1 = t0 + s.dot(r) / r.dot(r);
            if (t0 > t1) std::swap(t0, t1);
            return t0 <= 1 && t1 >= 0;
        } else return false; //Lines are parallel and not intersecting
    } else {
        // Lines are not parallel
        float t = qp.cross(s) / rxs;
        float u = qp.cross(r) / rxs;
        return t >= 0 && t <= 1 && u >= 0 && u <= 1;
    }
}

void LineSeg2D::print() const {
    std::cout << "LineSeg2D:" << std::endl;
    p1.print();
    p2.print();
}


bool Triangle2D::operator==(const Triangle2D &other) const {
    return (p1 == other.p1 && p2 == other.p2 && p3 == other.p3) ||
           (p1 == other.p2 && p2 == other.p3 && p3 == other.p1) ||
           (p1 == other.p3 && p2 == other.p1 && p3 == other.p2);
}

bool Triangle2D::has_inside(const Point2D &other) const {
    Vector2D v0 = p3 - p1;
    Vector2D v1 = p2 - p1;
    Vector2D v2 = other - p1;

    float dot00 = v0.dot(v0);
    float dot01 = v0.dot(v1);
    float dot02 = v0.dot(v2);
    float dot11 = v1.dot(v1);
    float dot12 = v1.dot(v2);

    float invDenom = 1 / (dot00 * dot11 - dot01 * dot01);
    float u = (dot11 * dot02 - dot01 * dot12) * invDenom;
    float v = (dot00 * dot12 - dot01 * dot02) * invDenom;

    return (u >= 0) && (v >= 0) && (u + v <= 1);
}

bool Triangle2D::intersect(const LineSeg2D &ls) const {
    if (has_inside(ls.getP1()) || has_inside(ls.getP2()))
        return true;

    if (ls.intersect(getEdge1()) || ls.intersect(getEdge2()) || ls.intersect(getEdge3()))
        return true;

    return false;
}

bool Triangle2D::intersect(const Triangle2D &t) const {
    if (has_inside(t.p1) || has_inside(t.p2) || has_inside(t.p3))
        return true;

    if (t.has_inside(p1) || t.has_inside(p2) || t.has_inside(p3))
        return true;

    if (t.intersect(getEdge1()) || t.intersect(getEdge2()) || t.intersect(getEdge3()))
        return true;

    return false;
}

void Triangle2D::print() const {
    std::cout << "Triangle2D:" << std::endl;
    p1.print();
    p2.print();
    p3.print();
}