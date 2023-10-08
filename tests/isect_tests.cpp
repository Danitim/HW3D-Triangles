#include <gtest/gtest.h>
#include "../intersection/intersect.hpp"


//Triangles in 3D intersection tests
TEST(Intersect3D, Case1) {
    Point3D a0(1, 0, 0);
    Point3D a1(0, 1, 0);
    Point3D a2(0, -2, 0);
    Triangle3D a(a0, a1, a2);

    Point3D b0(1, 0, -1);
    Point3D b1(-1, 0, 0);
    Point3D b2(0, 0, 1);
    Triangle3D b(b0, b1, b2);

    EXPECT_TRUE(tritri_intersection3D(a, b));
}

TEST(Intersect3D, Case2) {
    Point3D a0(1, 0, 0);
    Point3D a1(2, 0, 0);
    Point3D a2(-2, -1, 1);
    Triangle3D a(a0, a1, a2);

    Point3D b0(2, -2, 0);
    Point3D b1(2, -1, 5);
    Point3D b2(-1, 1, 3);
    Triangle3D b(b0, b1, b2);

    EXPECT_FALSE(tritri_intersection3D(a, b));
}

TEST(Intersect3D, Case3) {
    Point3D a0(1, 0, 0);
    Point3D a1(2, 0, 3);
    Point3D a2(-2, -1, 1);
    Triangle3D a(a0, a1, a2);

    Point3D b0(2, -2, 0);
    Point3D b1(2, -1, 5);
    Point3D b2(-1, 1, 3);
    Triangle3D b(b0, b1, b2);

    EXPECT_TRUE(tritri_intersection3D(a, b));
}

TEST(Intersect3D, Case4) {
    Point3D a0(1, 0, 0);
    Point3D a1(2, 0, 2);
    Point3D a2(-2, -1, 1);
    Triangle3D a(a0, a1, a2);

    Point3D b0(2, -2, 0);
    Point3D b1(2, -1, 5);
    Point3D b2(-1, 1, 3);
    Triangle3D b(b0, b1, b2);

    EXPECT_TRUE(tritri_intersection3D(a, b));
}

TEST(Intersect3D, Case5) {
    Point3D a0(1, 0, 0);
    Point3D a1(2, -2, 0);
    Point3D a2(-2, -1, 1);
    Triangle3D a(a0, a1, a2);

    Point3D b0(2, -2, 0);
    Point3D b1(2, -1, 5);
    Point3D b2(-1, 1, 3);
    Triangle3D b(b0, b1, b2);

    EXPECT_TRUE(tritri_intersection3D(a, b));
}

TEST(Intersect3D, Case6) {
    Point3D a0(1, 0, 0);
    Point3D a1(2, 2, 0);
    Point3D a2(-2, -1, 1);
    Triangle3D a(a0, a1, a2);

    Point3D b0(2, -2, 0);
    Point3D b1(2, -1, 5);
    Point3D b2(-1, 1, 3);
    Triangle3D b(b0, b1, b2);

    EXPECT_FALSE(tritri_intersection3D(a, b));
}

TEST(Intersect3D, Case7) {
    Point3D a0(1, 0, 0);
    Point3D a1(2, -2, 0);
    Point3D a2(-2, -1, 1);
    Triangle3D a(a0, a1, a2);

    Point3D b0(1, 0, 5);
    Point3D b1(2, -2, 5);
    Point3D b2(-2, -1, 6);
    Triangle3D b(b0, b1, b2);

    EXPECT_FALSE(tritri_intersection3D(a, b));
}

TEST(Intersect3D, Case8) {
    Point3D a0(-3, 2, 0);
    Point3D a1(3, 5, 0);
    Point3D a2(0, -4, 0);
    Triangle3D a(a0, a1, a2);

    Point3D b0(0, 4, 0);
    Point3D b1(6, -2, 0);
    Point3D b2(-3, -3, 0);
    Triangle3D b(b0, b1, b2);

    EXPECT_TRUE(tritri_intersection3D(a, b));
}


//Triangles in 2D intersection tests
TEST(Intersect2D, Case1) {
    Point2D a0(0, 0);
    Point2D b0(8, 0);
    Point2D c0(4, 4);
    Triangle2D a(a0, b0, c0);

    Point2D a1(0, 0);
    Point2D b1(8, 0);
    Point2D c1(4, 4);
    Triangle2D b(a1, b1, c1);

    EXPECT_TRUE(tritri_intersection2D(a, b));
}

TEST(Intersect2D, Case2) {
    Point2D a0(0, 0);
    Point2D b0(1, 0);
    Point2D c0(0, 1);
    Triangle2D a(a0, b0, c0);

    Point2D a1(0, 0);
    Point2D b1(1, 0);
    Point2D c1(0, 1);
    Triangle2D b(a1, b1, c1);

    EXPECT_TRUE(tritri_intersection2D(a, b));
}

TEST(Intersect2D, Case3) {
    Point2D a0(0, 0);
    Point2D b0(1, 0);
    Point2D c0(0, 1);
    Triangle2D a(a0, b0, c0);

    Point2D a1(1, 0);
    Point2D b1(2, 0);
    Point2D c1(2, 1);
    Triangle2D b(a1, b1, c1);

    EXPECT_TRUE(tritri_intersection2D(a, b));
}

TEST(Intersect2D, Case4) {
    Point2D a0(0, 0);
    Point2D b0(1, 0);
    Point2D c0(0, 1);
    Triangle2D a(a0, b0, c0);

    Point2D a1(1, 1);
    Point2D b1(1, 0);
    Point2D c1(0, 1);
    Triangle2D b(a1, b1, c1);

    EXPECT_TRUE(tritri_intersection2D(a, b));
}

TEST(Intersect2D, Case5) {
    Point2D a0(0, 0);
    Point2D b0(3, 0);
    Point2D c0(0, 3);
    Triangle2D a(a0, b0, c0);

    Point2D a1(1, 1);
    Point2D b1(1, 3);
    Point2D c1(3, 1);
    Triangle2D b(a1, b1, c1);

    EXPECT_TRUE(tritri_intersection2D(a, b));
}

TEST(Intersect2D, Case6) {
    Point2D a0(0, 0);
    Point2D b0(4, 0);
    Point2D c0(0, 4);
    Triangle2D a(a0, b0, c0);

    Point2D a1(1, 2);
    Point2D b1(2, 1);
    Point2D c1(3, 3);
    Triangle2D b(a1, b1, c1);

    EXPECT_TRUE(tritri_intersection2D(a, b));
}

TEST(Intersect2D, Case7) {
    Point2D a0(0, 1);
    Point2D b0(4, 1);
    Point2D c0(2, 3);
    Triangle2D a(a0, b0, c0);

    Point2D a1(0, 2);
    Point2D b1(4, 2);
    Point2D c1(2, 0);
    Triangle2D b(a1, b1, c1);

    EXPECT_TRUE(tritri_intersection2D(a, b));
}

TEST(Intersect2D, Case8) {
    Point2D a0(1, 1);
    Point2D b0(1, 0);
    Point2D c0(0, 1);
    Triangle2D a(a0, b0, c0);

    Point2D a1(-1, -1);
    Point2D b1(-1, 0);
    Point2D c1(0, -1);
    Triangle2D b(a1, b1, c1);

    EXPECT_FALSE(tritri_intersection2D(a, b));
}

int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}