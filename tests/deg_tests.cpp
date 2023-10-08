#include <gtest/gtest.h>
#include "../intersection/intersect.hpp"


//Segment and point intersection tests
/*The point lies on the segment*/
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

/*The point lies outside the segment, but on its continuation*/
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

/*The point lies outside the segment and not on its continuation*/
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

/*The point lies at the beginning of the segment*/
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

/*The point lies at the end of the segment*/
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


//Segment and segment intersection tests
/*The segments coincide completely*/
TEST(IntersectSegSeg3D, Case1) {
    Point3D a0(0, 0, 0);
    Point3D a1(1, 1, 1);
    Point3D a2(2, 2, 2);
    Triangle3D a(a0, a1, a2);

    Point3D b0(0, 0, 0);
    Point3D b1(1, 1, 1);
    Point3D b2(2, 2, 2);
    Triangle3D b(b0, b1, b2);

    EXPECT_TRUE(typed_intersection(a, b));
}

/*Segments partially intersect*/
TEST(IntersectSegSeg3D, Case2) {
    Point3D a0(0, 0, 0);
    Point3D a1(1, 1, 1);
    Point3D a2(2, 2, 2);
    Triangle3D a(a0, a1, a2);

    Point3D b0(1, 1, 1);
    Point3D b1(2, 2, 2);
    Point3D b2(3, 3, 3);
    Triangle3D b(b0, b1, b2);

    EXPECT_TRUE(typed_intersection(a, b));
}

/*The segments touch each other at one point*/
TEST(IntersectSegSeg3D, Case3) {
    Point3D a0(0, 0, 0);
    Point3D a1(1, 1, 1);
    Point3D a2(2, 2, 2);
    Triangle3D a(a0, a1, a2);

    Point3D b0(2, 2, 2);
    Point3D b1(3, 3, 3);
    Point3D b2(4, 4, 4);
    Triangle3D b(b0, b1, b2);

    EXPECT_TRUE(typed_intersection(a, b));
}

/*The segments are parallel and do not intersect*/
TEST(IntersectSegSeg3D, Case4) {
    Point3D a0(0, 0, 0);
    Point3D a1(1, 1, 1);
    Point3D a2(2, 2, 2);
    Triangle3D a(a0, a1, a2);

    Point3D b0(0, 1, 0);
    Point3D b1(1, 2, 1);
    Point3D b2(2, 3, 2);
    Triangle3D b(b0, b1, b2);

    EXPECT_FALSE(typed_intersection(a, b));
}

/*The segments are not parallel and do not intersect*/
TEST(IntersectSegSeg3D, Case5) {
    Point3D a0(0, 0, 0);
    Point3D a1(1, 1, 1);
    Point3D a2(2, 2, 2);
    Triangle3D a(a0, a1, a2);

    Point3D b0(3, 3, 4);
    Point3D b1(4, 4, 5);
    Point3D b2(5, 5, 8);
    Triangle3D b(b0, b1, b2);

    EXPECT_FALSE(typed_intersection(a, b));
}


//Triangle and point intersection tests
/*Point inside a triangle*/
TEST(IntersectTriPnt3D, Case1) {
    Point3D a0(0, 0, 0);
    Point3D a1(1, 0, 0);
    Point3D a2(0, 1, 0);
    Triangle3D a(a0, a1, a2);

    Point3D b0(0.33, 0.33, 0);
    Point3D b1(0.33, 0.33, 0);
    Point3D b2(0.33, 0.33, 0);
    Triangle3D b(b0, b1, b2);

    EXPECT_TRUE(typed_intersection(a, b));
}

/*A point outside the triangle, but on its plane*/
TEST(IntersectTriPnt3D, Case2) {
    Point3D a0(0, 0, 0);
    Point3D a1(1, 0, 0);
    Point3D a2(0, 1, 0);
    Triangle3D a(a0, a1, a2);

    Point3D b0(1.5, 0.5, 0);
    Point3D b1(1.5, 0.5, 0);
    Point3D b2(1.5, 0.5, 0);
    Triangle3D b(b0, b1, b2);

    EXPECT_FALSE(typed_intersection(a, b));
}

/*A point on one of the vertices of the triangle*/
TEST(IntersectTriPnt3D, Case3) {
    Point3D a0(0, 0, 0);
    Point3D a1(1, 0, 0);
    Point3D a2(0, 1, 0);
    Triangle3D a(a0, a1, a2);

    Point3D b0(0, 1, 0);
    Point3D b1(0, 1, 0);
    Point3D b2(0, 1, 0);
    Triangle3D b(b0, b1, b2);

    EXPECT_TRUE(typed_intersection(a, b));
}

/*A point on one of the sides of the triangle, but not on the vertex*/
TEST(IntersectTriPnt3D, Case4) {
    Point3D a0(0, 0, 0);
    Point3D a1(1, 0, 0);
    Point3D a2(0, 1, 0);
    Triangle3D a(a0, a1, a2);

    Point3D b0(0.5, 0, 0);
    Point3D b1(0.5, 0, 0);
    Point3D b2(0.5, 0, 0);
    Triangle3D b(b0, b1, b2);

    EXPECT_TRUE(typed_intersection(a, b));
}

/*Point outside the plane of the triangle*/
TEST(IntersectTriPnt3D, Case5) {
    Point3D a0(0, 0, 0);
    Point3D a1(1, 0, 0);
    Point3D a2(0, 1, 0);
    Triangle3D a(a0, a1, a2);

    Point3D b0(0.5, 0.5, 1);
    Point3D b1(0.5, 0.5, 1);
    Point3D b2(0.5, 0.5, 1);
    Triangle3D b(b0, b1, b2);

    EXPECT_FALSE(typed_intersection(a, b));
}


//Triangle and segment intersection tests
/*The segment is completely inside the triangle*/
TEST(IntersectTriSeg3D, Case1) {
    Point3D a0(0, 0, 0);
    Point3D a1(1, 0, 0);
    Point3D a2(0, 1, 0);
    Triangle3D a(a0, a1, a2);

    Point3D b0(0.25, 0.25, 0);
    Point3D b1(0.75, 0.25, 0);
    Point3D b2(0.75, 0.25, 0);
    Triangle3D b(b0, b1, b2);

    EXPECT_TRUE(typed_intersection(a, b));
}

/*One end of the segment is inside the triangle, the other is outside*/
TEST(IntersectTriSeg3D, Case2) {
    Point3D a0(0, 0, 0);
    Point3D a1(1, 0, 0);
    Point3D a2(0, 1, 0);
    Triangle3D a(a0, a1, a2);

    Point3D b0(0.33, 0.33, 0);
    Point3D b1(1.5, 1.5, 0);
    Point3D b2(1.5, 1.5, 0);
    Triangle3D b(b0, b1, b2);

    EXPECT_TRUE(typed_intersection(a, b));
}

/*The segment touches the triangle*/
TEST(IntersectTriSeg3D, Case3) {
    Point3D a0(0, 0, 0);
    Point3D a1(1, 0, 0);
    Point3D a2(0, 1, 0);
    Triangle3D a(a0, a1, a2);

    Point3D b0(0, 1, 0);
    Point3D b1(1, 1, 0);
    Point3D b2(1, 1, 0);
    Triangle3D b(b0, b1, b2);

    EXPECT_TRUE(typed_intersection(a, b));
}

/*Segment intersects triangle*/
TEST(IntersectTriSeg3D, Case4) {
    Point3D a0(0, 0, 0);
    Point3D a1(1, 0, 0);
    Point3D a2(0, 1, 0);
    Triangle3D a(a0, a1, a2);

    Point3D b0(-0.5, 0.5, 0);
    Point3D b1(1.5, 0.5, 0);
    Point3D b2(1.5, 0.5, 0);
    Triangle3D b(b0, b1, b2);

    EXPECT_TRUE(typed_intersection(a, b));
}

/*The segment and the triangle are on the same plane, but do not intersect*/
TEST(IntersectTriSeg3D, Case5) {
    Point3D a0(0, 0, 0);
    Point3D a1(1, 0, 0);
    Point3D a2(0, 1, 0);
    Triangle3D a(a0, a1, a2);

    Point3D b0(2, 0, 0);
    Point3D b1(3, 0, 0);
    Point3D b2(3, 0, 0);
    Triangle3D b(b0, b1, b2);

    EXPECT_FALSE(typed_intersection(a, b));
}

/*The segment and the triangle are in different planes and do not intersect*/
TEST(IntersectTriSeg3D, Case6) {
    Point3D a0(0, 0, 0);
    Point3D a1(1, 0, 0);
    Point3D a2(0, 1, 0);
    Triangle3D a(a0, a1, a2);

    Point3D b0(0.5, 0.5, 1);
    Point3D b1(1.5, 1.5, 1);
    Point3D b2(1.5, 1.5, 1);
    Triangle3D b(b0, b1, b2);

    EXPECT_FALSE(typed_intersection(a, b));
}


int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}