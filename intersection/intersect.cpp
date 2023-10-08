#include "intersect.hpp"

void intersect_each_with_each(std::set<int> &intersections, const std::vector<Triangle3D> &array) {
    for (int i=1; i < array.size(); ++i) {
        for (int j=0; j < i; ++j) {
            if (typed_intersection(array[i], array[j])) {
                intersections.insert(i);
                intersections.insert(j);
            }
        }
    }
    return;
}

bool typed_intersection(const Triangle3D &t0, const Triangle3D &t1) {
    short type0 = t0.get_type();
    short type1 = t1.get_type();

    switch(type0) {
    case 1:
        switch(type1) {
            case 1: {return t0.get_vertice(0).equal(t1.get_vertice(0)); break;}
            case 2: {Point3D p(t0); LineSeg3D ls(t1); return segpnt_intersection3D(ls, p); break;}
            case 3: {Point3D p(t0); return tripnt_intersection3D(t1, p); break;}
        }
    case 2:
        switch(type1) {
            case 1: {LineSeg3D ls(t0); Point3D p(t1); return segpnt_intersection3D(ls, p); break;}
            case 2: {LineSeg3D ls0(t0); LineSeg3D ls1(t1); return segseg_intersection3D(ls0, ls1); break;}
            case 3: {LineSeg3D ls(t0); return triseg_intersection3D(t1, ls); break;}
        }
    case 3:
        switch(type1) {
            case 1: {Point3D p(t1); return tripnt_intersection3D(t0, p); break;}
            case 2: {LineSeg3D ls(t1); return triseg_intersection3D(t0, ls); break;}
            case 3: {return tritri_intersection3D(t0, t1); break;}
        }
    }
    return false;
}


bool tritri_intersection3D(const Triangle3D &t0, const Triangle3D &t1) {
    //Compute the plane equation of T0
    Plane3D t0_plane(t0);
    
    //Compute the signed distances of the vertices of T1.
    std::vector<float> t1_signdist;
    signed_distances(t1_signdist, t1, t0_plane);

    //Compare the signs of signed distances. If they are all the same return false, otherwise, proceed to the next step.
    if (same_sign(t1_signdist[0], t1_signdist[1]) && same_sign(t1_signdist[1], t1_signdist[2]))
        return false;

    //Compute the plane equation of T1
    Plane3D t1_plane(t1);

    //Check if the planes are parallel
    if (t0_plane.coplanar(t1_plane)) {
        //Check if they are coincident
        if (t0_plane.equal(t1_plane)) {
            short axis_index = t0_plane.nearly_oriented_axis();
            Triangle2D t0_2d(t0, axis_index);
            Triangle2D t1_2d(t1, axis_index);
            //Project the triangles and perform a 2D triangle intersection test.
            return tritri_intersection2D(t0_2d, t1_2d);
        }
        else
            return false;
    }

    //Compute the signed distances of the vertices of T0.
    std::vector<float> t0_signdist;
    signed_distances(t0_signdist, t0, t1_plane);

    //Compare the signs of signed distances. If they are all the same return false, otherwise, proceed to the next step.
    if (same_sign(t0_signdist[0], t0_signdist[1]) && same_sign(t0_signdist[1], t0_signdist[2]))
        return false;
    
    //Compute intersection line.
    Line3D inter_line(t0_plane, t1_plane);

    //Make a copy of rearranged vertices of a triangle so that vertice[2] is on the other side of the plane.
    std::vector<Point3D> t0_vertices, t1_vertices;
    t0.copy_and_rearrange(t0_vertices, t0_signdist);
    t1.copy_and_rearrange(t1_vertices, t1_signdist);

    //Compute intervals of triangle and intersection line intersecton.
    std::vector<float> t0_interval, t1_interval;
    intersection_interval(t0_interval, t0_vertices, t0_signdist, inter_line);
    intersection_interval(t1_interval, t1_vertices, t1_signdist, inter_line);

    //Finally return whether the intervals are intersecting or not
    return ((t0_interval[0]<=t1_interval[1]) && (t0_interval[1]>=t1_interval[0]));
}