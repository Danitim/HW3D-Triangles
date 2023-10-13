#include <gtest/gtest.h>
#include "../geometry/geometry3D.hpp"

using namespace Geo3D;

TEST(Geo3DPointTest, ToPoint2DReturnsCorrectPoint) {
    Point p(1.0, 2.0, 3.0);

    Geo2D::Point p2D0 = p.to_point2D(0);
    Geo2D::Point p2D1 = p.to_point2D(1);
    Geo2D::Point p2D2 = p.to_point2D(2);

    EXPECT_TRUE(p2D0 == Geo2D::Point(2.0, 3.0));
    EXPECT_TRUE(p2D1 == Geo2D::Point(1.0, 3.0));
    EXPECT_TRUE(p2D2 == Geo2D::Point(1.0, 2.0));
}

TEST(Geo3DLineSegTest, ToLineSeg2DReturnsCorrectLineSeg) {
    Point p1(1.0, 2.0, 3.0);
    Point p2(4.0, 5.0, 6.0);
    LineSeg ls1(p1, p2);
    Geo2D::LineSeg ls2D1 = ls1.to_lineseg2D(0);
    EXPECT_TRUE(ls2D1 == Geo2D::LineSeg(Geo2D::Point(2.0, 3.0), Geo2D::Point(5.0, 6.0)));

    Point p3(0.0, 0.0, 0.0);
    Point p4(0.0, 0.0, 1.0);
    LineSeg ls2(p3, p4);
    Geo2D::LineSeg ls2D2 = ls2.to_lineseg2D(2);
    EXPECT_TRUE(ls2D2 == Geo2D::LineSeg(Geo2D::Point(0.0, 0.0), Geo2D::Point(0.0, 0.0)));

    Point p5(1.0, 2.0, 3.0);
    Point p6(4.0, 5.0, 6.0);
    LineSeg ls3(p5, p6);
    Geo2D::LineSeg ls2D3 = ls3.to_lineseg2D(1);
    EXPECT_TRUE(ls2D3 == Geo2D::LineSeg(Geo2D::Point(1.0, 3.0), Geo2D::Point(4.0, 6.0)));
}

TEST(Geo3DLineSegTest, IntersectPointReturnsTrueIfPointLiesOnLineSegment) {
    Point p1(1.0, 2.0, 3.0);
    Point p2(4.0, 5.0, 6.0);
    LineSeg ls(p1, p2);

    Point p3(2.0, 3.0, 4.0);
    Point p4(3.0, 4.0, 5.0);
    Point p5(1.0, 2.0, 3.0);
    Point p6(4.0, 5.0, 6.0);

    EXPECT_TRUE(ls.intersect(p3));
    EXPECT_TRUE(ls.intersect(p4));
    EXPECT_TRUE(ls.intersect(p5));
    EXPECT_TRUE(ls.intersect(p6));
}

TEST(Geo3DLineSegTest, IntersectPointReturnsFalseIfPointLiesOutsideSegmentButOnContinuation) {
    Point p1(1.0, 2.0, 3.0);
    Point p2(4.0, 5.0, 6.0);
    LineSeg ls(p1, p2);

    Point p3(0.0, 1.0, 2.0);
    Point p4(5.0, 6.0, 7.0);

    EXPECT_FALSE(ls.intersect(p3));
    EXPECT_FALSE(ls.intersect(p4));
}

TEST(Geo3DLineSegTest, IntersectPointReturnsFalseIfPointLiesOutsideSegmentAndNotOnContinuation) {
    Point p1(1.0, 2.0, 3.0);
    Point p2(4.0, 5.0, 6.0);
    LineSeg ls(p1, p2);

    Point p3(0.0, 0.0, 0.0);
    Point p4(0.0, 0.0, 1.0);
    Point p5(5.0, 5.0, 5.0);

    EXPECT_FALSE(ls.intersect(p3));
    EXPECT_FALSE(ls.intersect(p4));
    EXPECT_FALSE(ls.intersect(p5));
}

TEST(Geo3DLineSegTest, IntersectLineSegReturnsTrueIfSegmentsIntersect) {
    Point p1(1.0, 1.0, 1.0);
    Point p2(2.0, 2.0, 2.0);
    LineSeg ls1(p1, p2);

    Point p3(2.0, 2.0, 2.0);
    Point p4(3.0, 3.0, 3.0);
    LineSeg ls2(p3, p4);

    EXPECT_TRUE(ls1.intersect(ls2));
}

TEST(Geo3DLineSegTest, IntersectLineSegReturnsFalseIfSegmentsDoNotIntersect) {
    Point p1(1.0, 1.0, 1.0);
    Point p2(2.0, 2.0, 2.0);
    LineSeg ls1(p1, p2);

    Point p3(3.0, 3.0, 3.0);
    Point p4(4.0, 4.0, 4.0);
    LineSeg ls2(p3, p4);

    EXPECT_FALSE(ls1.intersect(ls2));
}

TEST(Geo3DLineSegTest, IntersectLineSegReturnsTrueIfSegmentsAreCollinearAndOverlap) {
    Point p1(1.0, 1.0, 1.0);
    Point p2(2.0, 2.0, 2.0);
    LineSeg ls1(p1, p2);

    Point p3(1.5, 1.5, 1.5);
    Point p4(3.0, 3.0, 3.0);
    LineSeg ls2(p3, p4);

    EXPECT_TRUE(ls1.intersect(ls2));
}

TEST(Geo3DLineSegTest, IntersectLineSegReturnsFalseIfSegmentsAreCollinearAndDoNotOverlap) {
    Point p1(1.0, 1.0, 1.0);
    Point p2(2.0, 2.0, 2.0);
    LineSeg ls1(p1, p2);

    Point p3(3.0, 3.0, 3.0);
    Point p4(4.0, 4.0, 4.0);
    LineSeg ls2(p3, p4);

    EXPECT_FALSE(ls1.intersect(ls2));
}

TEST(Geo3DLineSegTest, IntersectLineSegReturnsTrueIfSegmentsShareAnEndpoint) {
    Point p1(1.0, 1.0, 1.0);
    Point p2(2.0, 2.0, 2.0);
    LineSeg ls1(p1, p2);

    Point p3(2.0, 2.0, 2.0);
    Point p4(3.0, 3.0, 3.0);
    LineSeg ls2(p3, p4);

    EXPECT_TRUE(ls1.intersect(ls2));
}

TEST(Geo3DLineSegTest, IntersectLineSegReturnsFalseIfSegmentsAreParallelAndDoNotOverlap) {
    Point p1(1.0, 1.0, 1.0);
    Point p2(2.0, 2.0, 2.0);
    LineSeg ls1(p1, p2);

    Point p3(1.0, 2.0, 1.0);
    Point p4(2.0, 3.0, 2.0);
    LineSeg ls2(p3, p4);

    EXPECT_FALSE(ls1.intersect(ls2));
}

TEST(Geo3DLineSegTest, IntersectLineSegReturnsTrueIfSegmentsAreParallelAndOverlap) {
    Point p1(1.0, 1.0, 1.0);
    Point p2(2.0, 2.0, 2.0);
    LineSeg ls1(p1, p2);

    Point p3(0.5, 0.5, 0.5);
    Point p4(1.5, 1.5, 1.5);
    LineSeg ls2(p3, p4);

    EXPECT_TRUE(ls1.intersect(ls2));
}

TEST(Geo3DLineSegTest, IntersectLineSegReturnsTrueIfSegmentsShareAPoint) {
    Point p1(3.0, 1.0, 1.0);
    Point p2(1.0, 3.0, 3.0);
    LineSeg ls1(p1, p2);

    Point p3(1.0, 3.0, 1.0);
    Point p4(3.0, 1.0, 3.0);
    LineSeg ls2(p3, p4);

    EXPECT_TRUE(ls1.intersect(ls2));
}

TEST(Geo3DPlaneTest, IntersectionReturnsCorrectLine) {
    Plane pl1(1.0f, 1.0f, 1.0f, -1.0f);
    Plane pl2(-1.0f, -1.0f, 1.0f, -1.0f);
    Plane pl3(0.0f, 1.0f, 1.0f, 1.0f);

    Line l11 = pl1.intersection(pl2);
    Line l12 = pl2.intersection(pl3);
    Line l13 = pl1.intersection(pl3);

    EXPECT_TRUE(l11 == Line(Point(0.0f, 0.0f, 1.0f), Vector(2.0f, -2.0f, 0.0f)));
    EXPECT_TRUE(l12 == Line(Point(-0.33333f, -0.83333f, -0.16667f), Vector(-2.0f, 1.0f, -1.0f)));
    EXPECT_TRUE(l13 == Line(Point(2.0f, -0.5f, -0.5f), Vector(0.0f, -1.0f, 1.0f)));
}

TEST(Geo3DTriangleTest, ToLineSegReturnsCorrectLineSegFromTriangle) {
    Point p1(1.0, 1.0, 1.0);
    Point p2(2.0, 2.0, 2.0);
    Point p3(3.0, 3.0, 3.0);
    Triangle t1(p1, p2, p3);
    Triangle t2(p3, p1, p2);
    Triangle t3(p2, p3, p1);
    Triangle t4(p3, p2, p1);
    Triangle t5(p1, p3, p2);
    Triangle t6(p2, p1, p3);

    LineSeg ls(p1, p3);
    LineSeg ls1 = t1.to_lineseg();
    LineSeg ls2 = t2.to_lineseg();
    LineSeg ls3 = t3.to_lineseg();
    LineSeg ls4 = t4.to_lineseg();
    LineSeg ls5 = t5.to_lineseg();
    LineSeg ls6 = t6.to_lineseg();

    EXPECT_TRUE(ls1 == ls);
    EXPECT_TRUE(ls2 == ls);
    EXPECT_TRUE(ls3 == ls);
    EXPECT_TRUE(ls4 == ls);
    EXPECT_TRUE(ls5 == ls);
    EXPECT_TRUE(ls6 == ls);
}

TEST(Geo3DTriangleTest, ToLineSegReturnsCorrectLineSeg) {
    Point p1(1.0, 1.0, 1.0);
    Point p2(2.0, 2.0, 2.0);
    Point p3(3.0, 3.0, 3.0);
    Triangle t(p1, p2, p3);

    LineSeg ls = t.to_lineseg();

    EXPECT_TRUE(ls == LineSeg(p1, p3));
}

TEST(Geo3DTriangleTest, ToLineSegReturnsCorrectLineSegWhenVerticesAreCollinear) {
    Point p1(1.0, 1.0, 1.0);
    Point p2(2.0, 2.0, 2.0);
    Point p3(3.0, 3.0, 3.0);
    Triangle t(p1, p2, p3);

    Point p4(4.0, 4.0, 4.0);
    Point p5(5.0, 5.0, 5.0);
    Point p6(6.0, 6.0, 6.0);
    Triangle t2(p4, p5, p6);

    LineSeg ls1 = t.to_lineseg();
    LineSeg ls2 = t2.to_lineseg();

    EXPECT_TRUE(ls1 == LineSeg(p1, p3));
    EXPECT_TRUE(ls2 == LineSeg(p4, p6));
}

TEST(Geo3DTriangleTest, ToLineSegReturnsCorrectLineSegWhenVerticesAreEqual) {
    Point p1(1.0, 1.0, 1.0);
    Point p2(1.0, 1.0, 1.0);
    Point p3(1.0, 1.0, 1.0);
    Triangle t(p1, p2, p3);

    LineSeg ls = t.to_lineseg();

    EXPECT_TRUE(ls == LineSeg(p1, p3));
}

TEST(Geo3DTriangleTest, ToLineSegReturnsCorrectLineSegWhenVerticesAreOnDifferentPlanes) {
    Point p1(1.0, 1.0, 1.0);
    Point p2(2.0, 2.0, 2.0);
    Point p3(3.0, 3.0, 3.0);
    Triangle t(p1, p2, p3);

    Point p4(1.0, 2.0, 3.0);
    Point p5(2.0, 3.0, 4.0);
    Point p6(3.0, 4.0, 5.0);
    Triangle t2(p4, p5, p6);

    LineSeg ls1 = t.to_lineseg();
    LineSeg ls2 = t2.to_lineseg();

    EXPECT_TRUE(ls1 == LineSeg(p1, p3));
    EXPECT_TRUE(ls2 == LineSeg(p4, p6));
}

TEST(Geo3DTriangleTest, ToTriangle2DReturnsCorrectTriangleWhenAxisIndexIsX) {
    Point p1(1.0, 2.0, 3.0);
    Point p2(2.0, 3.0, 4.0);
    Point p3(3.0, 4.0, 5.0);
    Triangle t(p1, p2, p3);

    Geo2D::Triangle t2d = t.to_triangle2D(0);

    EXPECT_TRUE(t2d == Geo2D::Triangle(Geo2D::Point(2.0, 3.0), Geo2D::Point(3.0, 4.0), Geo2D::Point(4.0, 5.0)));
}

TEST(Geo3DTriangleTest, ToTriangle2DReturnsCorrectTriangleWhenAxisIndexIsY) {
    Point p1(1.0, 2.0, 3.0);
    Point p2(2.0, 3.0, 4.0);
    Point p3(3.0, 4.0, 5.0);
    Triangle t(p1, p2, p3);

    Geo2D::Triangle t2d = t.to_triangle2D(1);

    EXPECT_TRUE(t2d == Geo2D::Triangle(Geo2D::Point(1.0, 3.0), Geo2D::Point(2.0, 4.0), Geo2D::Point(3.0, 5.0)));
}

TEST(Geo3DTriangleTest, ToTriangle2DReturnsCorrectTriangleWhenAxisIndexIsZ) {
    Point p1(1.0, 2.0, 3.0);
    Point p2(2.0, 3.0, 4.0);
    Point p3(3.0, 4.0, 5.0);
    Triangle t(p1, p2, p3);

    Geo2D::Triangle t2d = t.to_triangle2D(2);

    EXPECT_TRUE(t2d == Geo2D::Triangle(Geo2D::Point(1.0, 2.0), Geo2D::Point(2.0, 3.0), Geo2D::Point(3.0, 4.0)));
}

TEST(Geo3DTriangleTest, GetTypeReturnsCorrectType) {
    // Test for point
    Point p1(1.0, 1.0, 1.0);
    Triangle t1(p1, p1, p1);
    EXPECT_EQ(t1.get_type(), 1);

    // Test for line segment
    Point p2(2.0, 2.0, 2.0);
    Triangle t2_1(p1, p2, p2);
    Triangle t2_2(p2, p1, p2);
    Triangle t2_3(p1, p1, p2);
    EXPECT_EQ(t2_1.get_type(), 2);
    EXPECT_EQ(t2_2.get_type(), 2);
    EXPECT_EQ(t2_3.get_type(), 2);

    // Test for triangle
    Point p3(1.0, 2.0, 3.0);
    Triangle t3_1(p1, p2, p3);
    Triangle t3_2(p2, p1, p3);
    Triangle t3_3(p3, p2, p1);
    Triangle t3_4(p3, p1, p2);
    EXPECT_EQ(t3_1.get_type(), 3);
    EXPECT_EQ(t3_2.get_type(), 3);
    EXPECT_EQ(t3_3.get_type(), 3);
    EXPECT_EQ(t3_4.get_type(), 3);
}

TEST(Geo3DTriangleTest, RearrangeVerticesReturnsTriangleWithOppositeSignDist) {
    Point p1(1.0, 1.0, 1.0);
    Point p2(2.0, 2.0, 2.0);
    Point p3(3.0, 3.0, 3.0);
    std::vector<float> sign_dist{1.0f, 2.0f, -3.0f};
    Triangle t1(p1, p2, p3);

    Triangle t2 = t1.rearrange_vertices(sign_dist);

    EXPECT_TRUE(t2.get_vertex(0) == p1 || t2.get_vertex(1) == p1);
    EXPECT_TRUE(t2.get_vertex(0) == p2 || t2.get_vertex(1) == p2);
    EXPECT_TRUE(t2.get_vertex(2) == p3);

    std::vector<float> sign_dist2{-1.0f, -2.0f, 3.0f};
    Triangle t3(p1, p3, p2);

    Triangle t4 = t3.rearrange_vertices(sign_dist2);

    EXPECT_TRUE(t4.get_vertex(0) == p1 || t4.get_vertex(1) == p1);
    EXPECT_TRUE(t4.get_vertex(0) == p3 || t4.get_vertex(1) == p3);
    EXPECT_TRUE(t4.get_vertex(2) == p2);

    std::vector<float> sign_dist3{-1.0f, 2.0f, -3.0f};
    Triangle t5(p2, p1, p3);

    Triangle t6 = t5.rearrange_vertices(sign_dist3);

    EXPECT_TRUE(t6.get_vertex(0) == p2 || t6.get_vertex(1) == p2);
    EXPECT_TRUE(t6.get_vertex(0) == p3 || t6.get_vertex(1) == p3);
    EXPECT_TRUE(t6.get_vertex(2) == p1);

    std::vector<float> sign_dist4{1.0f, -2.0f, 3.0f};
    Triangle t7(p2, p3, p1);

    Triangle t8 = t7.rearrange_vertices(sign_dist4);

    EXPECT_TRUE(t8.get_vertex(0) == p1 || t8.get_vertex(1) == p1);
    EXPECT_TRUE(t8.get_vertex(0) == p2 || t8.get_vertex(1) == p2);
    EXPECT_TRUE(t8.get_vertex(2) == p3);

    std::vector<float> sign_dist5{1.0f, -2.0f, -3.0f};
    Triangle t9(p3, p1, p2);

    Triangle t10 = t9.rearrange_vertices(sign_dist5);

    EXPECT_TRUE(t10.get_vertex(0) == p1 || t10.get_vertex(1) == p1);
    EXPECT_TRUE(t10.get_vertex(0) == p2 || t10.get_vertex(1) == p2);
    EXPECT_TRUE(t10.get_vertex(2) == p3);

    std::vector<float> sign_dist6{-1.0f, 2.0f, 3.0f};
    Triangle t11(p3, p2, p1);

    Triangle t12 = t11.rearrange_vertices(sign_dist6);

    EXPECT_TRUE(t12.get_vertex(0) == p1 || t12.get_vertex(1) == p1);
    EXPECT_TRUE(t12.get_vertex(0) == p2 || t12.get_vertex(1) == p2);
    EXPECT_TRUE(t12.get_vertex(2) == p3);
}

TEST(Geo3DTriangleTest, RearrangeVerticesReturnsTriangleTwoSameSignOneZeroSignDist) {
    Point p1(1.0, 1.0, 1.0);
    Point p2(2.0, 2.0, 2.0);
    Point p3(3.0, 3.0, 3.0);
    std::vector<float> sign_dist{1.0f, 2.0f, 0.0f};
    Triangle t1(p1, p2, p3);

    Triangle t2 = t1.rearrange_vertices(sign_dist);

    EXPECT_TRUE(t2.get_vertex(0) == p1 || t2.get_vertex(1) == p1);
    EXPECT_TRUE(t2.get_vertex(0) == p2 || t2.get_vertex(1) == p2);
    EXPECT_TRUE(t2.get_vertex(2) == p3);

    std::vector<float> sign_dist2{-1.0f, 0.0f, -3.0f};
    Triangle t3(p1, p2, p3);

    Triangle t4 = t3.rearrange_vertices(sign_dist2);

    EXPECT_TRUE(t4.get_vertex(0) == p1 || t4.get_vertex(1) == p1);
    EXPECT_TRUE(t4.get_vertex(0) == p3 || t4.get_vertex(1) == p3);
    EXPECT_TRUE(t4.get_vertex(2) == p2);

    std::vector<float> sign_dist3{0.0f, 2.0f, 3.0f};
    Triangle t5(p1, p2, p3);

    Triangle t6 = t5.rearrange_vertices(sign_dist3);

    EXPECT_TRUE(t6.get_vertex(0) == p2 || t6.get_vertex(1) == p2);
    EXPECT_TRUE(t6.get_vertex(0) == p3 || t6.get_vertex(1) == p3);
    EXPECT_TRUE(t6.get_vertex(2) == p1);
}

TEST(Geo3DTriangleTest, RearrangeVerticesReturnsTriangleOnePositiveOneNegativeOneZeroSignDist) {
    Point p1(1.0, 1.0, 1.0);
    Point p2(2.0, 2.0, 2.0);
    Point p3(3.0, 3.0, 3.0);
    std::vector<float> sign_dist{0.0f, -2.0f, 1.0f};
    Triangle t1(p1, p2, p3);

    Triangle t2 = t1.rearrange_vertices(sign_dist);

    EXPECT_TRUE(t2.get_vertex(0) == p3 || t2.get_vertex(1) == p3);
    EXPECT_TRUE(t2.get_vertex(0) == p2 || t2.get_vertex(1) == p2);
    EXPECT_TRUE(t2.get_vertex(2) == p1);

    std::vector<float> sign_dist2{-1.0f, 0.0f, 3.0f};
    Triangle t3(p1, p2, p3);

    Triangle t4 = t3.rearrange_vertices(sign_dist2);

    EXPECT_TRUE(t4.get_vertex(0) == p1 || t4.get_vertex(1) == p1);
    EXPECT_TRUE(t4.get_vertex(0) == p3 || t4.get_vertex(1) == p3);
    EXPECT_TRUE(t4.get_vertex(2) == p2);
}

TEST(Geo3DTriangleTest, RearrangeVerticesReturnsTriangleTwoZeroSignDist) {
    Point p1(1.0, 1.0, 1.0);
    Point p2(2.0, 2.0, 2.0);
    Point p3(3.0, 3.0, 3.0);
    std::vector<float> sign_dist{0.0f, 1.0f, 0.0f};
    Triangle t1(p1, p2, p3);

    Triangle t2 = t1.rearrange_vertices(sign_dist);

    EXPECT_TRUE(t2.get_vertex(0) == p1 || t2.get_vertex(1) == p1);
    EXPECT_TRUE(t2.get_vertex(0) == p3 || t2.get_vertex(1) == p3);
    EXPECT_TRUE(t2.get_vertex(2) == p2);

    std::vector<float> sign_dist2{0.0f, 0.0f, -1.0f};
    Triangle t3(p1, p2, p3);

    Triangle t4 = t3.rearrange_vertices(sign_dist2);

    EXPECT_TRUE(t4.get_vertex(0) == p1 || t4.get_vertex(1) == p1);
    EXPECT_TRUE(t4.get_vertex(0) == p2 || t4.get_vertex(1) == p2);
    EXPECT_TRUE(t4.get_vertex(2) == p3);
}

TEST(Geo3DTriangleTest, GetPlaneReturnsCorrectPlane) {
    Point p1(0.0f, 0.0f, 0.0f);
    Point p2(1.0f, 0.0f, 0.0f);
    Point p3(0.0f, 1.0f, 0.0f);
    Triangle t(p1, p2, p3);

    Plane pl = t.get_plane();

    EXPECT_TRUE(pl.equal(Plane(0.0f, 0.0f, 1.0f, 0.0f)));
}

TEST(Geo3DTriangleTest, SignedDistancesReturnsCorrectSignedDistances) {
    Point p1(1.0f, 1.0f, 1.0f);
    Point p2(-1.0f, 0.0f, 0.0f);
    Point p3(0.0f, -1.0f, 0.0f);
    Triangle t(p1, p2, p3);

    std::vector<float> sign_dist = t.signed_distances(Vector(1.0f, 1.0f, 1.0f), -1.0f);

    EXPECT_FLOAT_EQ(sign_dist[0], 2.0f);
    EXPECT_FLOAT_EQ(sign_dist[1], -2.0f);
    EXPECT_FLOAT_EQ(sign_dist[2], -2.0f);
}

TEST(Geo3DTriangleTest, IntersectionIntervalReturnsCorrectInterval) {
    Point p1(0.0f, -1.0f, 0.0f);
    Point p2(-1.0f, 0.0f, 0.0f);
    Point p3(1.0f, 1.0f, 1.0f);
    Triangle t(p1, p2, p3);

    Plane pl(1.0f, 1.0f, 1.0f, -1.0f);
    Line l = t.get_plane().intersection(pl);
    std::vector<float> sign_dist = {-2.0f, -2.0f, 2.0f};

    std::vector<float> interval = t.intersection_interval(sign_dist, l.getP(), l.getD());

    EXPECT_FLOAT_EQ(interval[0], -2.0f);
    EXPECT_FLOAT_EQ(interval[1], 2.0f);
}

TEST(Geo3DTriangleTest, IntersectPointReturnsCorrectValue) {
    Point a(0.0f, 0.0f, 0.0f);
    Point b(1.0f, 0.0f, 0.0f);
    Point c(0.0f, 1.0f, 0.0f);
    Triangle t(a, b, c);

    Point p1(0.33f, 0.33f, 0.0f);
    Point p2(1.5f, 0.5f, 0.0f);
    Point p3(0.0f, 1.0f, 0.0f);
    Point p4(0.5f, 0.0f, 0.0f);
    Point p5(0.5f, 0.5f, 1.0f);

    EXPECT_TRUE(t.has_inside(p1));
    EXPECT_FALSE(t.has_inside(p2));
    EXPECT_TRUE(t.has_inside(p3));
    EXPECT_TRUE(t.has_inside(p4));
    EXPECT_FALSE(t.has_inside(p5));
}

TEST(Geo3DTriangleTest, IntersectReturnsTrueIfLineSegIsCompletelyInsideTriangle) {
    Point p1(0.0, 0.0, 0.0);
    Point p2(0.0, 1.0, 0.0);
    Point p3(1.0, 0.0, 0.0);
    Triangle t(p1, p2, p3);

    Point p4(0.25, 0.25, 0.0);
    Point p5(0.75, 0.25, 0.0);
    LineSeg ls(p4, p5);

    EXPECT_TRUE(t.intersect(ls));
}

TEST(Geo3DTriangleTest, IntersectReturnsTrueIfOneEndOfLineSegIsInsideTriangleAndOtherIsOutside) {
    Point p1(0.0, 0.0, 0.0);
    Point p2(0.0, 1.0, 0.0);
    Point p3(1.0, 0.0, 0.0);
    Triangle t(p1, p2, p3);

    Point p4(0.25, 0.25, 0.0);
    Point p5(1.25, 0.25, 0.0);
    LineSeg ls(p4, p5);

    EXPECT_TRUE(t.intersect(ls));
}

TEST(Geo3DTriangleTest, IntersectReturnsTrueIfLineSegTouchesTriangle) {
    Point p1(0.0, 0.0, 0.0);
    Point p2(0.0, 1.0, 0.0);
    Point p3(1.0, 0.0, 0.0);
    Triangle t(p1, p2, p3);

    Point p4(0.5, 0.5, 0.0);
    Point p5(1.5, 0.5, 0.0);
    LineSeg ls(p4, p5);

    EXPECT_TRUE(t.intersect(ls));
}

TEST(Geo3DTriangleTest, IntersectReturnsTrueIfLineSegIntersectsTriangle) {
    Point p1(0.0, 0.0, 0.0);
    Point p2(0.0, 1.0, 0.0);
    Point p3(1.0, 0.0, 0.0);
    Triangle t(p1, p2, p3);

    Point p4(0.3, 0.3, 0.5);
    Point p5(0.3, 0.3, -0.5);
    LineSeg ls(p4, p5);

    EXPECT_TRUE(t.intersect(ls));
}

TEST(Geo3DTriangleTest, IntersectReturnsTrueIfLineSegIntersectsTrianglesEdge) {
    Point p1(0.0, 0.0, 0.0);
    Point p2(0.0, 1.0, 0.0);
    Point p3(1.0, 0.0, 0.0);
    Triangle t(p1, p2, p3);

    Point p4(0.5, 0.5, 0.5);
    Point p5(0.5, 0.5, -0.5);
    LineSeg ls(p4, p5);

    EXPECT_TRUE(t.intersect(ls));
}

TEST(Geo3DTriangleTest, IntersectReturnsTrueIfLineSegIntersectsTrianglesVertex) {
    Point p1(0.0, 0.0, 0.0);
    Point p2(0.0, 1.0, 0.0);
    Point p3(1.0, 0.0, 0.0);
    Triangle t(p1, p2, p3);

    Point p4(0.5, 0.5, 0.5);
    Point p5(1.5, -0.5, -0.5);
    LineSeg ls(p4, p5);

    EXPECT_TRUE(t.intersect(ls));
}

TEST(Geo3DTriangleTest, IntersectReturnsFalseIfLineSegAndTriangleAreOnSamePlaneButDoNotIntersect) {
    Point p1(0.0, 0.0, 0.0);
    Point p2(0.0, 1.0, 0.0);
    Point p3(1.0, 0.0, 0.0);
    Triangle t(p1, p2, p3);

    Point p4(0.5, 0.5, 1.0);
    Point p5(0.5, 0.5, 2.0);
    LineSeg ls(p4, p5);

    EXPECT_FALSE(t.intersect(ls));
}

TEST(Geo3DTriangleTest, IntersectReturnsFalseIfLineSegAndTriangleAreInDifferentPlanesAndDoNotIntersect) {
    Point p1(0.0, 0.0, 0.0);
    Point p2(0.0, 1.0, 0.0);
    Point p3(1.0, 0.0, 0.0);
    Triangle t(p1, p2, p3);

    Point p4(0.5, 0.5, 0.5);
    Point p5(0.5, 0.6, 1.5);
    LineSeg ls(p4, p5);

    EXPECT_FALSE(t.intersect(ls));
}


int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}