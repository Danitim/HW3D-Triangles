#include "intersection/intersect.hpp"

int main() {
    int n;
    std::cin >> n;
    std::vector<Triangle3D> triangles;
    std::set<int> intersections;
    for (int i=0; i<n; ++i) {
        Point3D v0, v1, v2;
        std::cin >> v0 >> v1 >> v2;
        Triangle3D t(v0, v1, v2);
        triangles.push_back(t);
    }

    intersect_each_with_each(intersections, triangles);
    for (int const &index : intersections)
        std::cout << index << std::endl;
}