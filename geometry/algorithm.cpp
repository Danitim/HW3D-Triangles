#include "algorithm.hpp"

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

bool tritri_intersection2D(const Triangle2D &t1, const Triangle2D &t2) {
    for (int i=0; i<3; ++i)
        if (t2.has_inside(t1.vertices[i]))
            return true;
    for (int i=0; i<3; ++i)
        if (t1.has_inside(t2.vertices[i]))
            return true;
    
    for (int i=0; i<3; ++i)
        for (int j=0; j<3; ++j)
            if (segseg_intersection2D(t1.vertices[i], t1.vertices[(i+1)%3], t2.vertices[i], t2.vertices[(i+1)%3]))
                return true;

    return false;
}

bool triseg_intersection2D(const Triangle2D &t, const LineSeg2D &ls) {
    if (t.has_inside(ls.p0) || t.has_inside(ls.p1))
        return true;

    for (int i=0; i<3; ++i)
        if (segseg_intersection2D(t.vertices[i], t.vertices[(i+1)%3], ls.p0, ls.p1))
            return true;

    return false;
}

bool segseg_intersection2D(const Point2D &p1, const Point2D &q1, const Point2D &p2, const Point2D &q2) {
    float d1 = cross({p2.x - p1.x, p2.y - p1.y}, {q1.x - p1.x, q1.y - p1.y});
    float d2 = cross({q2.x - p1.x, q2.y - p1.y}, {q1.x - p1.x, q1.y - p1.y});
    float d3 = cross({p1.x - p2.x, p1.y - p2.y}, {q2.x - p2.x, q2.y - p2.y});
    float d4 = cross({q1.x - p2.x, q1.y - p2.y}, {q2.x - p2.x, q2.y - p2.y});
    if ((d1 * d2 < 0) && (d3 * d4 < 0)) return true;
    return false;
}