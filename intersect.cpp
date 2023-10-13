#include "intersect.hpp"

void intersect_each_each(std::set<int>& intersections, std::vector<Geo3D::Triangle>& triangles) {
    for (int i=0; i<triangles.size(); ++i) {
        for (int j=i+1; j<triangles.size(); ++j) {
            if (triangles[i].intersect(triangles[j])) {
                intersections.insert(i);
                intersections.insert(j);
            }
        }
    }
}