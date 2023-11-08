#include <gtest/gtest.h>
#include "../geometry/geometry3D.hpp"

using namespace Geo3D;

TEST(TriTriIntersectionTest, Case1) {
    // Located far from each other.
    Triangle t1(Point(0, 0, 0), Point(1, 0, 0), Point(0, 1, 0));
    Triangle t2(Point(10, 10, 10), Point(11, 10, 10), Point(10, 11, 10));

    EXPECT_FALSE(t1.intersect(t2));
}

TEST(TriTriIntersectionTest, Case2) {
    // Nearby, but do not touch or intersect.
    Triangle t1(Point(0, 0, 0), Point(1, 0, 0), Point(0, 1, 0));
    Triangle t2(Point(1, 1, 1), Point(2, 1, 1), Point(1, 2, 1));

    EXPECT_FALSE(t1.intersect(t2));
}

TEST(TriTriIntersectionTest, Case3) {
    // One or more edges of one triangle intersect another triangle.
    Triangle t1(Point(0, 0, 0), Point(2, 0, 0), Point(0, 2, 0));
    Triangle t2(Point(-1, 0, -1), Point(-1, 3, -1), Point(2, 2, 1));

    EXPECT_TRUE(t1.intersect(t2));
}

TEST(TriTriIntersectionTest, Case4) {
    // The vertex of one triangle is inside the other, but its edges do not intersect with the other triangle.
    Triangle t1(Point(0, 0, 0), Point(2, 0, 0), Point(0, 2, 0));
    Triangle t2(Point(0.5, 0.5, 0), Point(3, 1, 1), Point(1, 3, 1));

    EXPECT_TRUE(t1.intersect(t2));
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}