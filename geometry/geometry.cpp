#include "geometry.hpp"

//Point2D methods
Point2D::Point2D(float x, float y): x(x), y(y) {};

Point2D::Point2D(const Point3D &p, short axis_index) {
    switch (axis_index) {
    case 0:
        x = p.y; y = p.z; break;
    case 1:
        x = p.x; y = p.z; break;
    case 2:
        x = p.x; y = p.y; break;
    }
}

void Point2D::print() const{
    std::cout << std::setprecision(3) << "(" << x << "; " << y << ")" << std::endl;
    return;
}

bool Point2D::equal(const Point2D &a) const {
    return (std::abs(x-a.x) < cnst::EPS) && (std::abs(y-a.y) < cnst::EPS);
}


//Vector2D methods
Vector2D::Vector2D() {x=0; y=0;}
Vector2D::Vector2D(float x, float y): x(x), y(y) {}
Vector2D::Vector2D(const Point2D &other): x(other.x), y(other.y) {}

Vector2D Vector2D::operator+(Vector2D &other) {
    return Vector2D(x+other.x, y+other.y); 
}
Vector2D Vector2D::operator-(Vector2D &other) {
    return Vector2D(x-other.x, y-other.y); 
}

void Vector2D::print() const{
    std::cout << std::setprecision(3) << "(" << x << "; " << y << ")" << std::endl;
    return;
}

bool Vector2D::equal(const Vector2D &a) const {
    return (fabs(x-a.x) < cnst::EPS) && (fabs(y-a.y) < cnst::EPS);
}


//Point3D methods
Point3D::Point3D() {x=0; y=0; z=0;}
Point3D::Point3D(float x, float y, float z): x(x), y(y), z(z) {};
Point3D::Point3D(const Triangle3D &t): x(t.vertices[0].x), y(t.vertices[0].y), z(t.vertices[0].z) {};

std::istream& operator>>(std::istream &input, Point3D &a) {
    input >> a.x >> a.y >> a.z; return input;
}

void Point3D::print() const{
    std::cout << std::setprecision(3) << "(" << x << "; " << y << "; " << z << ")" << std::endl;
    return;
}

bool Point3D::equal(const Point3D &a) const {
    return (fabs(x-a.x) < cnst::EPS) && (fabs(y-a.y) < cnst::EPS) && (fabs(z-a.z) < cnst::EPS);
}


//Vector3D methods
Vector3D::Vector3D() {x=0; y=0; z=0;}
Vector3D::Vector3D(float x, float y, float z): x(x), y(y), z(z) {}
Vector3D::Vector3D(const Point3D &other): x(other.x), y(other.y), z(other.z) {}

Vector3D operator+(Vector3D &a, Vector3D &b) {
    return Vector3D(a.x+b.x, a.y+b.y, a.z+b.z);
}
Vector3D operator+(const Point3D &a, const Point3D &b) {
    return Vector3D(a.x+b.x, a.y+b.y, a.z+b.z);
}
Vector3D operator-(Vector3D &a, Vector3D &b) {
    return Vector3D(a.x-b.x, a.y-b.y, a.z-b.z);
}
Vector3D operator-(const Point3D &a, const Point3D &b) {
    return Vector3D(a.x-b.x, a.y-b.y, a.z-b.z);
}

void Vector3D::print() const{
    std::cout << std::setprecision(3) << "(" << x << "; " << y << "; " << z << ")" << std::endl;
    return;
}

bool Vector3D::equal(const Vector3D &a) const {
    return (fabs(x-a.x) < cnst::EPS) && (fabs(y-a.y) < cnst::EPS) && (fabs(z-a.z) < cnst::EPS);
}

bool Vector3D::collinear(const Vector3D &v) const {
    Vector3D v_zero;
    Vector3D prod;
    cross(prod, *this, v);
    return prod.equal(v_zero);
}


//Triangle2D methods
Triangle2D::Triangle2D(const Point2D &v0, const Point2D &v1, const Point2D &v2) {
    vertices.push_back(v0);
    vertices.push_back(v1);
    vertices.push_back(v2);
    return;
}

Triangle2D::Triangle2D(const Triangle3D &t, short axis_index) {
    Point2D a(t.vertices[0], axis_index);
    Point2D b(t.vertices[1], axis_index);
    Point2D c(t.vertices[2], axis_index);

    vertices.push_back(a);
    vertices.push_back(b);
    vertices.push_back(c);
}

bool Triangle2D::has_inside(const Point2D &p) const {
    for (int i=0; i<3; i++) {
        Point2D edge(vertices[(i+1)%3].x - vertices[i].x,
                        vertices[(i+1)%3].y - vertices[i].y);
        Point2D vec(p.x - vertices[i].x, p.y - vertices[i].y);
        if ((edge.x*vec.y - edge.y*vec.x) < 0) return false;
    }
    return true;
}

void Triangle2D::print() const {
    std::cout << "2D triangle:" << std::endl;
    vertices[0].print();
    vertices[1].print();
    vertices[2].print();
    std::cout << std::endl;
}

bool Triangle2D::equal(const Triangle2D &t) const {
    return vertices[0].equal(vertices[0])
        && vertices[1].equal(vertices[1])
        && vertices[2].equal(vertices[2]);
}

bool Triangle2D::valid() const {
    float a = vertices[0].x * (vertices[1].y - vertices[2].y)
            + vertices[1].x * (vertices[2].y - vertices[0].y)
            + vertices[2].x * (vertices[0].y - vertices[1].y);
    return (abs(a) < cnst::EPS ? false : true);
}


//Triangle3D methods
Triangle3D::Triangle3D (const Point3D &v0, const Point3D &v1, const Point3D &v2) {
    vertices.push_back(v0);
    vertices.push_back(v1);
    vertices.push_back(v2);

    //Is it a point?
    if (v0.equal(v1) && v0.equal(v2)) {type = 1; return;}

    //Is it a line segment?
    Vector3D a = {v1.x - v0.x, v1.y - v0.y, v1.z - v0.z};
    Vector3D b = {v2.x - v0.x, v2.y - v0.y, v2.z - v0.z};
    if (a.collinear(b)) {type = 2; return;}

    //Now this is a triangle
    type = 3; return;
}

void Triangle3D::copy_and_rearrange(std::vector<Point3D> &v, const std::vector<float> &sign_dist) const {
    if (same_sign(sign_dist[0], sign_dist[1])) {
        v.push_back(vertices[0]);
        v.push_back(vertices[1]);
        v.push_back(vertices[2]);
        return;
    }

    if (same_sign(sign_dist[1], sign_dist[2])) {
        v.push_back(vertices[2]);
        v.push_back(vertices[1]);
        v.push_back(vertices[0]);
        return;
    }

    v.push_back(vertices[0]);
    v.push_back(vertices[2]);
    v.push_back(vertices[1]);
    return;
}

Point3D Triangle3D::get_vertice(short index) const {
    return vertices[index];
}

short Triangle3D::get_type() const {
    return type;
}

void Triangle3D::print() const {
    std::cout << "3D triangle:" << std::endl;
    vertices[0].print();
    vertices[1].print();
    vertices[2].print();
    std::cout << std::endl;
    return;
}

bool Triangle3D::equal(const Triangle3D &t) const {
    return vertices[0].equal(t.vertices[0])
        && vertices[1].equal(t.vertices[1])
        && vertices[2].equal(t.vertices[2]);
}

bool Triangle3D::valid() const {
    float side0 = dist3D(vertices[0], vertices[1]);
    float side1 = dist3D(vertices[1], vertices[2]);
    float side2 = dist3D(vertices[2], vertices[0]);

    return ((side0+side1>side2) && (side1+side2>side0) && (side2+side0>side1));
}


//Plane3D methods
Plane3D::Plane3D(float a, float b, float c, float d) {
    n.x = a;
    n.y = b;
    n.z = c;
    this->d = d;
    return;
}

Plane3D::Plane3D(const Triangle3D &t) {
    Vector3D a = t.vertices[0];
    Vector3D b = t.vertices[1];
    Vector3D c = t.vertices[2];
    cross(n, (b - a), (c - a));
    d = -dot(n, a);
    return;
}

short Plane3D::nearly_oriented_axis() {
    if ((n.x >= n.y) && (n.x >= n.z))
        return 0;
    if ((n.y >= n.x) && (n.y >= n.z))
        return 1;
    return 2;
}

void Plane3D::print() const{
    std::cout << "3D Plane:" << std::endl;
    std::cout << n.x << " " << n.y << " " << n.z << " " << d << std::endl;
    std::cout << std::endl;
    return;
}

bool Plane3D::coplanar(const Plane3D &p) {
    return n.collinear(p.n);
}

bool Plane3D::equal(const Plane3D &p) {
    if ((p.d == 0) && (d == 0)) return true;
    if (p.n.x!=0) return coplanar(p) && ((fabs(n.x/p.n.x - d/p.d)) < cnst::EPS);
    if (p.n.y!=0) return coplanar(p) && ((fabs(n.y/p.n.y - d/p.d)) < cnst::EPS);
    if (p.n.z!=0) return coplanar(p) && ((fabs(n.z/p.n.z - d/p.d)) < cnst::EPS);
    //So basically we cannot be here, so chill
    return false;
}


//Line3D methods
Line3D::Line3D(const Point3D &p, const Vector3D &d) {
    this->p.x = p.x; this->p.y = p.y; this->p.z = p.z;
    this->d.x = d.x; this->d.y = d.y; this->d.z = d.z;
}

Line3D::Line3D(const Plane3D &p0, const Plane3D &p1) {
    Vector3D prod;
    cross(prod, p0.n, p1.n);
    d.x = prod.x; d.y = prod.y; d.z = prod.z;

    float n1n2dot = dot(p0.n, p1.n);
    float n1sqr = dot(p0.n, p0.n);
    float n2sqr = dot(p1.n, p1.n);
    float a = ((-p1.d)*n1n2dot - (-p0.d)*n2sqr) / (n1n2dot*n1n2dot - n1sqr*n2sqr);
    float b = ((-p0.d)*n1n2dot - (-p1.d)*n1sqr) / (n1n2dot*n1n2dot - n1sqr*n2sqr);
    p.x = a*p0.n.x + b*p1.n.x; p.y = a*p0.n.y + b*p1.n.y; p.z = a*p0.n.z + b*p1.n.z; 
    return;
}

bool Line3D::equal(const Line3D &l) const {
    return (d.collinear(l.d)) && (p.equal(l.p));
}

void Line3D::print() const {
    std::cout << "3D line:" << std::endl;
    p.print();
    d.print();
    std::cout << std::endl;
    return;
}


//LineSeg3D methods
LineSeg3D::LineSeg3D(const Point3D &p0, const Point3D &p1) {
    this->p0 = p0; this->p1 = p1;
}
LineSeg3D::LineSeg3D(const Triangle3D &t) {
    Vector3D v01 = t.vertices[0] - t.vertices[1];
    Vector3D v02 = t.vertices[0] - t.vertices[2];
    Vector3D v12 = t.vertices[1] - t.vertices[2];

    float d01 = dot(v01, v01);
    float d02 = dot(v02, v02);
    float d12 = dot(v12, v12);

    if ((d01 >= d02) && (d01 >= d12)) {p0 = t.vertices[0]; p1 = t.vertices[1];}
    else if ((d02 >= d01) && (d02 >= d12)) {p0 = t.vertices[0]; p1 = t.vertices[2];}
    else {p0 = t.vertices[1]; p1 = t.vertices[2];}
}

bool LineSeg3D::equal(const LineSeg3D &ls) const{
    return p0.equal(ls.p0) && p1.equal(ls.p1);
}

void LineSeg3D::print() const {
    std::cout << "3D Line Segment:" << std::endl;
    p0.print();
    p1.print();
    return;
}


//Other geometric functions
bool same_sign(float a, float b) {
    if ((fabs(a) < cnst::EPS) || (fabs(b) < cnst::EPS))
        return false;
    return (a*b >= 0.0f);
}

float dot(const Vector3D &a, const Vector3D &b) {
    return a.x*b.x + a.y*b.y + a.z*b.z;
}
void cross(Vector3D &prod, const Vector3D &a, const Vector3D &b) {
    prod.x = a.y*b.z - a.z*b.y;
    prod.y = a.z*b.x - a.x*b.z;
    prod.z = a.x*b.y - a.y*b.x;
    return;
}
float cross(const Vector2D &a, const Vector2D &b) {
    return a.x*b.y - a.y*b.x;
}

float dist3D(const Point3D &p1, const Point3D &p2) {
    return hypot(hypot(p1.x-p2.x, p1.y-p2.y), p1.z-p2.z);
}

void signed_distances(std::vector<float> &signdist, const Triangle3D &t, const Plane3D &p) {
    signdist.push_back(dot(p.n, t.vertices[0]) + p.d);
    signdist.push_back(dot(p.n, t.vertices[1]) + p.d);
    signdist.push_back(dot(p.n, t.vertices[2]) + p.d);
    return;
}

void intersection_interval(std::vector<float> &interval, std::vector<Point3D> &v, const std::vector<float> signdist, Line3D &l) {
    std::vector<float> proj;
    proj.push_back(dot(l.d, (v[0]-l.p)));
    proj.push_back(dot(l.d, (v[1]-l.p)));
    proj.push_back(dot(l.d, (v[2]-l.p)));

    interval.push_back(proj[0] + (proj[2] - proj[0]) * signdist[0] / (signdist[0] - signdist[2]));
    interval.push_back(proj[1] + (proj[2] - proj[1]) * signdist[1] / (signdist[1] - signdist[2]));

    if (interval[0] > interval[1])
        std::swap(interval[0], interval[1]);

    return;
}

bool check_intersection2D(const Triangle2D &t1, const Triangle2D &t2) {
    for (int i=0; i<3; ++i)
        if (t2.has_inside(t1.vertices[i]))
            return true;
    for (int i=0; i<3; ++i)
        if (t1.has_inside(t2.vertices[i]))
            return true;
    
    for (int i=0; i<3; ++i)
        for (int j=0; j<3; ++j)
            if (edges_intersect(t1.vertices[i], t1.vertices[(i+1)%3], t2.vertices[i], t2.vertices[(i+1)%3]))
            return true;
    return false;
}

bool edges_intersect(const Point2D &p1, const Point2D &q1, const Point2D &p2, const Point2D &q2) {
    float d1 = cross({p2.x - p1.x, p2.y - p1.y}, {q1.x - p1.x, q1.y - p1.y});
    float d2 = cross({q2.x - p1.x, q2.y - p1.y}, {q1.x - p1.x, q1.y - p1.y});
    float d3 = cross({p1.x - p2.x, p1.y - p2.y}, {q2.x - p2.x, q2.y - p2.y});
    float d4 = cross({q1.x - p2.x, q1.y - p2.y}, {q2.x - p2.x, q2.y - p2.y});
    if ((d1 * d2 < 0) && (d3 * d4 < 0)) return true;
    return false;
}