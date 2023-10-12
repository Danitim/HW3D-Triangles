#include <gtest/gtest.h>
#include "../geometry/geometry2D.hpp"

using namespace geo2D;

TEST(LineSeg2DTest, IntersectTest) {
  // Two line segments intersect at a point
  LineSeg line1(Point(0, 0), Point(2, 2));
  LineSeg line2(Point(0, 2), Point(2, 0));
  EXPECT_TRUE(line1.intersect(line2));

  // Two line segments do not intersect
  LineSeg line3(Point(0, 0), Point(2, 2));
  LineSeg line4(Point(3, 3), Point(4, 4));
  EXPECT_FALSE(line3.intersect(line4));

  // Two line segments overlap
  LineSeg line5(Point(0, 0), Point(2, 2));
  LineSeg line6(Point(1, 1), Point(3, 3));
  EXPECT_TRUE(line5.intersect(line6));

  // Two line segments share an endpoint
  LineSeg line7(Point(0, 0), Point(2, 2));
  LineSeg line8(Point(2, 2), Point(3, 3));
  EXPECT_TRUE(line7.intersect(line8));

  // Two line segments are collinear but do not overlap
  LineSeg line9(Point(0, 0), Point(2, 2));
  LineSeg line10(Point(3, 3), Point(4, 4));
  EXPECT_FALSE(line9.intersect(line10));
}

TEST(Triangle2DTest, HasInsideTest) {
  Point p1(0, 0);
  Point p2(0, 2);
  Point p3(2, 0);
  Triangle triangle(p1, p2, p3);

  // Test a point inside the triangle
  Point insidePoint(0.5, 0.5);
  EXPECT_TRUE(triangle.has_inside(insidePoint));

  // Test a point outside the triangle
  Point outsidePoint(3, 3);
  EXPECT_FALSE(triangle.has_inside(outsidePoint));

  // Test a point on the edge of the triangle
  Point edgePoint(1, 0);
  EXPECT_TRUE(triangle.has_inside(edgePoint));

  // Test a point on the triangle's vertex
  Point vertexPoint(2, 0);
  EXPECT_TRUE(triangle.has_inside(vertexPoint));
}

TEST(Triangle2DTest, IntersectLineSegTest) {
  Point p1(0, 0);
  Point p2(0, 2);
  Point p3(2, 0);
  Triangle triangle(p1, p2, p3);

  // Test a line segment that intersects the triangle
  LineSeg intersectingLine(Point(1, 1), Point(3, 3));
  EXPECT_TRUE(triangle.intersect(intersectingLine));

  // Test a line segment that does not intersect the triangle
  LineSeg nonIntersectingLine(Point(3, 3), Point(4, 4));
  EXPECT_FALSE(triangle.intersect(nonIntersectingLine));

  // Test a line segment that is entirely inside the triangle
  LineSeg insideLine(Point(1, 1), Point(1, 0));
  EXPECT_TRUE(triangle.intersect(insideLine));

  // Test a line segment that shares an endpoint with the triangle
  LineSeg sharedEndpointLine(Point(0, 0), Point(1, 1));
  EXPECT_TRUE(triangle.intersect(sharedEndpointLine));

  // Test a line segment that is collinear with the triangle but does not intersect it
  LineSeg collinearLine(Point(3, 3), Point(4, 4));
  EXPECT_FALSE(triangle.intersect(collinearLine));
}

TEST(Triangle2DTest, IntersectTest) {
  // Test two triangles that intersect
  Triangle triangle1(Point(0, 0), Point(0, 2), Point(2, 0));
  Triangle triangle2(Point(1, 1), Point(1, 3), Point(3, 1));
  EXPECT_TRUE(triangle1.intersect(triangle2));

  // Test two triangles that do not intersect
  Triangle triangle3(Point(0, 0), Point(0, 2), Point(2, 0));
  Triangle triangle4(Point(3, 3), Point(3, 4), Point(4, 3));
  EXPECT_FALSE(triangle3.intersect(triangle4));

  // Test two triangles that share an edge
  Triangle triangle5(Point(0, 0), Point(0, 2), Point(2, 0));
  Triangle triangle6(Point(0, 2), Point(2, 0), Point(2, 2));
  EXPECT_TRUE(triangle5.intersect(triangle6));

  // Test two triangles that share a vertex
  Triangle triangle7(Point(0, 0), Point(0, 2), Point(2, 0));
  Triangle triangle8(Point(0, 0), Point(2, 0), Point(2, 2));
  EXPECT_TRUE(triangle7.intersect(triangle8));

  // Test two triangles that are identical
  Triangle triangle9(Point(0, 0), Point(0, 2), Point(2, 0));
  Triangle triangle10(Point(0, 0), Point(0, 2), Point(2, 0));
  EXPECT_TRUE(triangle9.intersect(triangle10));
}


int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}