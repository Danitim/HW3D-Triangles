#include "intersect.hpp"

int main() {
    int n;
    std::cin >> n;
    std::vector<Geo3D::Triangle> triangles;
    for (int i=0; i<n; ++i) {
        Geo3D::Triangle t;
        t.input();
        triangles.push_back(t);
    }

    std::set<int> intersections;
    intersect_each_each(intersections, triangles);
    for (int const &index : intersections)
        std::cout << index << std::endl;
}