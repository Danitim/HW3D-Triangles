#include "geometry3D.hpp"


Geo2D::Point Geo3D::Point::to_point2D(short axis_index) const {
    if (axis_index == 0) return Geo2D::Point(y, z);
    if (axis_index == 1) return Geo2D::Point(x, z);
    return Geo2D::Point(x, y);
}

void Geo3D::Line::print() const {
    std::cout << "3D Line: " << std::endl;
    std::cout << "Origin: "; p.print();
    std::cout << "Direction: "; d.print();
}

Geo2D::LineSeg Geo3D::LineSeg::to_lineseg2D(short axis_index) const {
    if (axis_index == 0) return Geo2D::LineSeg(p1.to_point2D(axis_index), p2.to_point2D(axis_index));
    if (axis_index == 1) return Geo2D::LineSeg(p1.to_point2D(axis_index), p2.to_point2D(axis_index));
    return Geo2D::LineSeg(p1.to_point2D(axis_index), p2.to_point2D(axis_index));
}

bool Geo3D::LineSeg::intersect(const Point& p) const {
    Vector ax = p - p1;
    Vector ab = p2 - p1;

    if (!ax.collinear(ab)) return false;

    float axab = ax.dot(ab);
    return (axab >= 0) && (axab <= ab.dot(ab));
}

static bool projections_intersect(float a1, float a2, float b1, float b2) {
    if (a1 > a2) std::swap(a1, a2);
    if (b1 > b2) std::swap(b1, b2);
    return std::max(a1, b1) <= std::min(a2, b2);
}

bool Geo3D::LineSeg::intersect(const LineSeg& ls) const {
    Vector d1 = getDirection();
    Vector d2 = ls.getDirection();
    Vector x = ls.getP1() - p1;

    Vector n = d1.cross(d2);
    if (n == Vector()) {
        if (!d1.collinear(x)) return false;
        short axis_index = d1.max_component();
        Geo2D::LineSeg ls1_2d = to_lineseg2D(axis_index);
        Geo2D::LineSeg ls2_2d = ls.to_lineseg2D(axis_index);
        return ls1_2d.intersect(ls2_2d);
    }

    float t = x.dot(d2.cross(n)) / n.dot(d1.cross(d2));
    float u = x.dot(d1.cross(n)) / n.dot(d1.cross(d2));
    return (t >= 0) && (t <= 1) && (u >= 0) && (u <= 1);
}

void Geo3D::LineSeg::print() const {
    std::cout << "3D Line Segment: " << std::endl;
    std::cout << "P1: "; p1.print();
    std::cout << "P2: "; p2.print();
}

Geo3D::Line Geo3D::Plane::intersection(const Plane& other) const {
    Vector other_n = other.getNormal();
    float other_d = other.getD();
    Vector d = n.cross(other_n);

    float n1n2dot = n.dot(other_n);
    float n1sqr = n.dot(n);
    float n2sqr = other_n.dot(other_n);
    float a = ((-other_d)*n1n2dot - (-this->d)*n2sqr) / (n1n2dot*n1n2dot - n1sqr*n2sqr);
    float b = ((-this->d)*n1n2dot - (-other_d)*n1sqr) / (n1n2dot*n1n2dot - n1sqr*n2sqr);
    Point p = Point(a*n.getX() + b*other_n.getX(), a*n.getY() + b*other_n.getY(), a*n.getZ() + b*other_n.getZ());

    return Line(p, d);
}

bool Geo3D::Plane::coplanar(const Plane& other) const {
    return n.collinear(other.getNormal());
}

//Not optimized, just for testing purpose
bool Geo3D::Plane::equal(const Plane& other) const {
    Vector self_n = n.normalize();
    Vector other_n = other.getNormal().normalize();
    return self_n.collinear(other_n) && self_n.dot(other_n) > 0.0f &&
           fabs(d/n.length() - other.getD()/other.n.length()) < cnst::EPS;
}

void Geo3D::Plane::print() const {
    std::cout << "3D Plane: " << std::endl;
    std::cout << "Normal: "; n.print();
    std::cout << "D: " << d << std::endl;
}

Geo3D::Point Geo3D::Triangle::to_point() const {
    return Point(p1.getX(), p1.getY(), p1.getZ());
}

Geo3D::LineSeg Geo3D::Triangle::to_lineseg() const {
    Vector v12 = p2 - p1;
    Vector v13 = p3 - p1;
    Vector v23 = p3 - p2;

    float d12 = v12.dot(v12);
    float d13 = v13.dot(v12);
    float d23 = v23.dot(v23);

    if (d12 > d13 && d12 > d23) return LineSeg(p1, p2);
    if (d13 > d12 && d13 > d23) return LineSeg(p1, p3);
    return LineSeg(p2, p3);
}

Geo2D::Triangle Geo3D::Triangle::to_triangle2D(short axis_index) const {
    Geo2D::Point p1_2d = p1.to_point2D(axis_index);
    Geo2D::Point p2_2d = p2.to_point2D(axis_index);
    Geo2D::Point p3_2d = p3.to_point2D(axis_index);
    return Geo2D::Triangle(p1_2d, p2_2d, p3_2d);
}

/*Rearrange vertices of t triangle so if there are two vertices with same sign of sign dist
    and one with different sign or a zero, the one with different sign or zero is the third one.
    If there are one vertices with positive sign dist, one zero sign dist and one negative sign dist,
    the one with zero sign dist is the third one.
    If there are two vertices with zero sign dist and one with non-zero sign dist,
    the one with non-zero sign dist is the third one*/
Geo3D::Triangle Geo3D::Triangle::rearrange_vertices(std::vector<float> &sign_dist) const{
    Triangle t = *this;
    short counter = 0;
    for (int i=0; i<3; ++i)
        if (fabs(sign_dist[i]) < cnst::EPS) counter++;

    if (counter == 0) {
        if (sign_dist[0]*sign_dist[2] > 0.0f) {
            std::swap(t.p2, t.p3);
            std::swap(sign_dist[1], sign_dist[2]);
        } else if (sign_dist[1]*sign_dist[2] > 0.0f) {
            std::swap(t.p1, t.p3);
            std::swap(sign_dist[0], sign_dist[2]);
        }
    } else if (counter == 1) {
        if (fabs(sign_dist[0]) < cnst::EPS) {
            std::swap(t.p1, t.p3);
            std::swap(sign_dist[0], sign_dist[2]);
        } else if (fabs(sign_dist[1]) < cnst::EPS) {
            std::swap(t.p2, t.p3);
            std::swap(sign_dist[1], sign_dist[2]);
        }
    } else {
        if (fabs(sign_dist[0]) > 0.0f) {
            std::swap(t.p1, t.p3);
            std::swap(sign_dist[0], sign_dist[2]);
        } else if (fabs(sign_dist[1]) > 0.0f) {
            std::swap(t.p2, t.p3);
            std::swap(sign_dist[1], sign_dist[2]);
        }
    }
    return t;
}

Geo3D::Plane Geo3D::Triangle::get_plane() const {
    Vector v12 = p2 - p1;
    Vector v13 = p3 - p1;
    Vector n = v12.cross(v13);
    return Plane(n, -n.dot(p1.to_vector()));
}

std::vector<float> Geo3D::Triangle::signed_distances(const Vector &n, float d) const {
    std::vector<float> sign_dist(3);
    sign_dist[0] = n.dot(p1.to_vector()) + d;
    sign_dist[1] = n.dot(p2.to_vector()) + d;
    sign_dist[2] = n.dot(p3.to_vector()) + d;
    return sign_dist;
}

std::vector<float> Geo3D::Triangle::intersection_interval(const std::vector<float> sign_dist, Point line_p, Vector line_d) const {
    std::vector<float> proj(3);
    proj[0] = line_d.dot(p1 - line_p);
    proj[1] = line_d.dot(p2 - line_p);
    proj[2] = line_d.dot(p3 - line_p);

    std::vector<float> interval(2);
    interval[0] = proj[0] + (proj[2] - proj[0]) * sign_dist[0] / (sign_dist[0] - sign_dist[2]);
    interval[1] = proj[1] + (proj[2] - proj[1]) * sign_dist[1] / (sign_dist[1] - sign_dist[2]);

    if (interval[0] > interval[1])
        std::swap(interval[0], interval[1]);
    
    return interval;
}

bool Geo3D::Triangle::has_inside(const Point& p) const {
    Vector v0 = p - p1;
    Vector v1 = p - p2;
    Vector v2 = p - p3;

    Vector n = (p2 - p1).cross(p3 - p1);
    if (fabs(n.dot(v0)) > cnst::EPS)
        return false;

    float d00 = v0.dot(v0);
    float d01 = v0.dot(v1);
    float d02 = v0.dot(v2);
    float d11 = v1.dot(v1);
    float d12 = v2.dot(v2);
    float d = d00*d11 - d01*d01;
    
    if (fabs(d) < cnst::EPS)
        return true;

    float u = (d11*d02 - d01*d12)/d;
    float v = (d00*d12 - d01*d02)/d;
    return (u >= 0) && (v >= 0) && (u + v <= 1);
}

bool Geo3D::Triangle::intersect(const LineSeg& ls) const {
    Vector v1 = p2 - p1;
    Vector v2 = p3 - p1;
    Vector d = ls.getDirection();

    Vector n = v1.cross(v2);
    Vector h = d.cross(v2);
    float a = v1.dot(h);
    if (fabs(d.dot(n)) < cnst::EPS) {
        if (fabs((ls.getP1() - p1).dot(n)) > cnst::EPS) return false;
        short axis_index = n.max_component();
        Geo2D::Triangle t_2d = to_triangle2D(axis_index);
        Geo2D::LineSeg ls_2d = ls.to_lineseg2D(axis_index);
        return t_2d.intersect(ls_2d);
    }

    float f = 1.0f / a;
    Vector s = ls.getP1() - p1;
    float u = f * s.dot(h);
    if (u < 0.0f || u > 1.0f) return false;

    Vector q = s.cross(v1);
    float v = f * d.dot(q);
    if (v < 0.0f || u + v > 1.0f) return false;

    float t = f * v2.dot(q);
    return (t >= 0.0f) && (t <= 1.0f);
}

bool Geo3D::Triangle::intersect(const Triangle& t) const {
    Plane p = get_plane();

    std::vector<float> t_sign_dist = t.signed_distances(p.getNormal(), p.getD());

    if (fabs(t_sign_dist[0]) > cnst::EPS && fabs(t_sign_dist[1]) > cnst::EPS && fabs(t_sign_dist[2]) > cnst::EPS)
        if (t_sign_dist[0]*t_sign_dist[1] >= 0.0f && t_sign_dist[1]*t_sign_dist[2] >= 0.0f)
            return false;
    Plane t_plane = t.get_plane();

    if (p.coplanar(t_plane)) {
        if (p.equal(t_plane)) {
            short axis_index = p.getNormal().max_component();
            Geo2D::Triangle t1_2d = to_triangle2D(axis_index);
            Geo2D::Triangle t2_2d = t.to_triangle2D(axis_index);
            return t1_2d.intersect(t2_2d);
        }
        else return false;
    }

    std::vector<float> sign_dist = signed_distances(t_plane.getNormal(), t_plane.getD());
    if (fabs(t_sign_dist[0]) > cnst::EPS && fabs(t_sign_dist[1]) > cnst::EPS && fabs(t_sign_dist[2]) > cnst::EPS)
        if (sign_dist[0]*sign_dist[1] >= 0.0f && sign_dist[1]*sign_dist[2] >= 0.0f)
            return false;
    
    Line intersection_line = p.intersection(t_plane);

    Triangle t1_rotated = rearrange_vertices(sign_dist);
    Triangle t2_rotated = t.rearrange_vertices(t_sign_dist);

    std::vector<float> interval1 = t1_rotated.intersection_interval(sign_dist, intersection_line.getP(), intersection_line.getD());
    std::vector<float> interval2 = t2_rotated.intersection_interval(t_sign_dist, intersection_line.getP(), intersection_line.getD());

    return (interval1[0] <= interval2[1]) && (interval2[0] <= interval1[1]);
}

short Geo3D::Triangle::degeneration_type() const {
    if (p1 == p2 && p2 == p3) return 1;
    if ((p2 - p1).collinear(p3 - p1)) return 2;
    return 3;
}

bool Geo3D::Triangle::equal(const Triangle &t) const {
    Point other_p1 = t.getP1(); Point other_p2 = t.getP2(); Point other_p3 = t.getP3();
    return (p1 == other_p1 || p1 == other_p2 || p1 == other_p3) &&
            (p2 == other_p1 || p2 == other_p2 || p2 == other_p3) &&
            (p3 == other_p1 || p3 == other_p2 || p3 == other_p3);
}

void Geo3D::Triangle::print() const {
    std::cout << "3D Triangle: " << std::endl;
    std::cout << "P1: "; p1.print();
    std::cout << "P2: "; p2.print();
    std::cout << "P3: "; p3.print();
}