#include "intersect.hpp"

int main() {
    int n;
    std::cin >> n;
    std::vector<Triangle3D> triangles;
    std::set<int> intersections;
    for (int i=0; i<n; ++i) {
        Point3D v0, v1, v2;
        std::cin >> v0 >> v1 >> v2;
        Triangle3D t(v0, v1, v2);
        if (!t.valid()) {std::cout << "Not a valid triangle. Exiting..." << std::endl; exit(-1);}
        triangles.push_back(t);
    }

    find_intersecting_triangles(intersections, triangles);
    for (int const &index : intersections)
        std::cout << index << " ";
    std::cout << std::endl;
}