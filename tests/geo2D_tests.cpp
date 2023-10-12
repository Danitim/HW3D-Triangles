#include <gtest/gtest.h>
#include "../geometry/geometry2D.hpp"

TEST(LineSeg2DTest, IntersectTest) {
  // Two line segments intersect at a point
  LineSeg2D line1(Point2D(0, 0), Point2D(2, 2));
  LineSeg2D line2(Point2D(0, 2), Point2D(2, 0));
  EXPECT_TRUE(line1.intersect(line2));

  // Two line segments do not intersect
  LineSeg2D line3(Point2D(0, 0), Point2D(2, 2));
  LineSeg2D line4(Point2D(3, 3), Point2D(4, 4));
  EXPECT_FALSE(line3.intersect(line4));

  // Two line segments overlap
  LineSeg2D line5(Point2D(0, 0), Point2D(2, 2));
  LineSeg2D line6(Point2D(1, 1), Point2D(3, 3));
  EXPECT_TRUE(line5.intersect(line6));

  // Two line segments share an endpoint
  LineSeg2D line7(Point2D(0, 0), Point2D(2, 2));
  LineSeg2D line8(Point2D(2, 2), Point2D(3, 3));
  EXPECT_TRUE(line7.intersect(line8));

  // Two line segments are collinear but do not overlap
  LineSeg2D line9(Point2D(0, 0), Point2D(2, 2));
  LineSeg2D line10(Point2D(3, 3), Point2D(4, 4));
  EXPECT_FALSE(line9.intersect(line10));
}

TEST(Triangle2DTest, HasInsideTest) {
  Point2D p1(0, 0);
  Point2D p2(0, 2);
  Point2D p3(2, 0);
  Triangle2D triangle(p1, p2, p3);

  // Test a point inside the triangle
  Point2D insidePoint(0.5, 0.5);
  EXPECT_TRUE(triangle.has_inside(insidePoint));

  // Test a point outside the triangle
  Point2D outsidePoint(3, 3);
  EXPECT_FALSE(triangle.has_inside(outsidePoint));

  // Test a point on the edge of the triangle
  Point2D edgePoint(1, 0);
  EXPECT_TRUE(triangle.has_inside(edgePoint));

  // Test a point on the triangle's vertex
  Point2D vertexPoint(2, 0);
  EXPECT_TRUE(triangle.has_inside(vertexPoint));
}

TEST(Triangle2DTest, IntersectLineSegTest) {
  Point2D p1(0, 0);
  Point2D p2(0, 2);
  Point2D p3(2, 0);
  Triangle2D triangle(p1, p2, p3);

  // Test a line segment that intersects the triangle
  LineSeg2D intersectingLine(Point2D(1, 1), Point2D(3, 3));
  EXPECT_TRUE(triangle.intersect(intersectingLine));

  // Test a line segment that does not intersect the triangle
  LineSeg2D nonIntersectingLine(Point2D(3, 3), Point2D(4, 4));
  EXPECT_FALSE(triangle.intersect(nonIntersectingLine));

  // Test a line segment that is entirely inside the triangle
  LineSeg2D insideLine(Point2D(1, 1), Point2D(1, 0));
  EXPECT_TRUE(triangle.intersect(insideLine));

  // Test a line segment that shares an endpoint with the triangle
  LineSeg2D sharedEndpointLine(Point2D(0, 0), Point2D(1, 1));
  EXPECT_TRUE(triangle.intersect(sharedEndpointLine));

  // Test a line segment that is collinear with the triangle but does not intersect it
  LineSeg2D collinearLine(Point2D(3, 3), Point2D(4, 4));
  EXPECT_FALSE(triangle.intersect(collinearLine));
}

TEST(Triangle2DTest, IntersectTest) {
  // Test two triangles that intersect
  Triangle2D triangle1(Point2D(0, 0), Point2D(0, 2), Point2D(2, 0));
  Triangle2D triangle2(Point2D(1, 1), Point2D(1, 3), Point2D(3, 1));
  EXPECT_TRUE(triangle1.intersect(triangle2));

  // Test two triangles that do not intersect
  Triangle2D triangle3(Point2D(0, 0), Point2D(0, 2), Point2D(2, 0));
  Triangle2D triangle4(Point2D(3, 3), Point2D(3, 4), Point2D(4, 3));
  EXPECT_FALSE(triangle3.intersect(triangle4));

  // Test two triangles that share an edge
  Triangle2D triangle5(Point2D(0, 0), Point2D(0, 2), Point2D(2, 0));
  Triangle2D triangle6(Point2D(0, 2), Point2D(2, 0), Point2D(2, 2));
  EXPECT_TRUE(triangle5.intersect(triangle6));

  // Test two triangles that share a vertex
  Triangle2D triangle7(Point2D(0, 0), Point2D(0, 2), Point2D(2, 0));
  Triangle2D triangle8(Point2D(0, 0), Point2D(2, 0), Point2D(2, 2));
  EXPECT_TRUE(triangle7.intersect(triangle8));

  // Test two triangles that are identical
  Triangle2D triangle9(Point2D(0, 0), Point2D(0, 2), Point2D(2, 0));
  Triangle2D triangle10(Point2D(0, 0), Point2D(0, 2), Point2D(2, 0));
  EXPECT_TRUE(triangle9.intersect(triangle10));
}


int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}