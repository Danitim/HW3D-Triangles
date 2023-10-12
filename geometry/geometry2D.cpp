#include "geometry2D.hpp"

bool geo2D::LineSeg::operator==(const geo2D::LineSeg &other) const {
    return (p1 == other.p1 && p2 == other.p2) ||
           (p1 == other.p2 && p2 == other.p1);
}

bool geo2D::LineSeg::intersect(const geo2D::LineSeg &ls) const {
    geo2D::Vector r = getDirection();
    geo2D::Vector s = ls.getDirection();
    geo2D::Vector qp = ls.getP1() - p1;

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

void geo2D::LineSeg::print() const {
    std::cout << "2D LineSeg:" << std::endl;
    p1.print();
    p2.print();
}


bool geo2D::Triangle::operator==(const geo2D::Triangle &other) const {
    return (p1 == other.p1 && p2 == other.p2 && p3 == other.p3) ||
           (p1 == other.p2 && p2 == other.p3 && p3 == other.p1) ||
           (p1 == other.p3 && p2 == other.p1 && p3 == other.p2);
}

bool geo2D::Triangle::has_inside(const geo2D::Point &p) const {
    geo2D::Vector v0 = p3 - p1;
    geo2D::Vector v1 = p2 - p1;
    geo2D::Vector v2 = p - p1;

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

bool geo2D::Triangle::intersect(const geo2D::LineSeg &ls) const {
    if (has_inside(ls.getP1()) || has_inside(ls.getP2()))
        return true;

    if (ls.intersect(getEdge1()) || ls.intersect(getEdge2()) || ls.intersect(getEdge3()))
        return true;

    return false;
}

bool geo2D::Triangle::intersect(const geo2D::Triangle &t) const {
    if (has_inside(t.p1) || has_inside(t.p2) || has_inside(t.p3))
        return true;

    if (t.has_inside(p1) || t.has_inside(p2) || t.has_inside(p3))
        return true;

    if (t.intersect(getEdge1()) || t.intersect(getEdge2()) || t.intersect(getEdge3()))
        return true;

    return false;
}

void geo2D::Triangle::print() const {
    std::cout << "2D Triangle:" << std::endl;
    p1.print();
    p2.print();
    p3.print();
}