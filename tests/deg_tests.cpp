#include <gtest/gtest.h>
#include "../intersection/intersect.hpp"


//Segment and point intersection tests
TEST(IntersectSegPnt3D, Case1) {
    Point3D a0(0, 0, 0);
    Point3D a1(1, 1, 1);
    Point3D a2(2, 2, 2);
    Triangle3D a(a0, a1, a2);

    Point3D b0(1, 1, 1);
    Point3D b1(1, 1, 1);
    Point3D b2(1, 1, 1);
    Triangle3D b(b0, b1, b2);

    EXPECT_TRUE(typed_intersection(a, b));
}

TEST(IntersectSegPnt3D, Case2) {
    Point3D a0(0, 0, 0);
    Point3D a1(1, 1, 1);
    Point3D a2(2, 2, 2);
    Triangle3D a(a0, a1, a2);

    Point3D b0(3, 3, 3);
    Point3D b1(3, 3, 3);
    Point3D b2(3, 3, 3);
    Triangle3D b(b0, b1, b2);

    EXPECT_FALSE(typed_intersection(a, b));
}

TEST(IntersectSegPnt3D, Case3) {
    Point3D a0(0, 0, 0);
    Point3D a1(1, 1, 1);
    Point3D a2(2, 2, 2);
    Triangle3D a(a0, a1, a2);

    Point3D b0(1, 2, 3);
    Point3D b1(1, 2, 3);
    Point3D b2(1, 2, 3);
    Triangle3D b(b0, b1, b2);

    EXPECT_FALSE(typed_intersection(a, b));
}

TEST(IntersectSegPnt3D, Case4) {
    Point3D a0(0, 0, 0);
    Point3D a1(1, 1, 1);
    Point3D a2(2, 2, 2);
    Triangle3D a(a0, a1, a2);

    Point3D b0(0, 0, 0);
    Point3D b1(0, 0, 0);
    Point3D b2(0, 0, 0);
    Triangle3D b(b0, b1, b2);

    EXPECT_TRUE(typed_intersection(a, b));
}

TEST(IntersectSegPnt3D, Case5) {
    Point3D a0(0, 0, 0);
    Point3D a1(1, 1, 1);
    Point3D a2(2, 2, 2);
    Triangle3D a(a0, a1, a2);

    Point3D b0(2, 2, 2);
    Point3D b1(2, 2, 2);
    Point3D b2(2, 2, 2);
    Triangle3D b(b0, b1, b2);

    EXPECT_TRUE(typed_intersection(a, b));
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}