#include <gtest/gtest.h>
#include "../geometry/geometry.hpp"
#include "../geometry/algorithm.hpp"


//Point2D tests
TEST(Point2DEqualTest, HandlesNonEqual) {
    Point2D a(1.0f, 2.0f);
    Point2D b(-1.0f, 5.0f);
    Point2D c(-2.5f, 2.5f);
    Point2D d(5.0f, 5.0f);
    EXPECT_FALSE(a.equal(b));
    EXPECT_FALSE(a.equal(c));
    EXPECT_FALSE(a.equal(d));
    EXPECT_FALSE(b.equal(c));
    EXPECT_FALSE(b.equal(d));
    EXPECT_FALSE(c.equal(d));
}

TEST(Point2DEqualTest, HandlesEqual) {
    Point2D a(1.0f, 1.0f);
    Point2D b(1.0f, 1.000001f);
    Point2D c(1.0f, (1.0f-0.0000001f));
    EXPECT_TRUE(a.equal(b));
    EXPECT_TRUE(a.equal(c));
    EXPECT_TRUE(b.equal(c));
}


//Point3D tests
TEST(Point3DEqualTest, HandlesNonEqual) {
    Point3D a(1.0f, 2.0f, 2.0f);
    Point3D b(-1.0f, 5.0f, -4.0f);
    Point3D c(-2.5f, 2.5f, 1.01f);
    Point3D d(-2.5f, 2.5f, 1.0f);
    EXPECT_FALSE(a.equal(b));
    EXPECT_FALSE(a.equal(c));
    EXPECT_FALSE(a.equal(d));
    EXPECT_FALSE(b.equal(c));
    EXPECT_FALSE(b.equal(d));
    EXPECT_FALSE(c.equal(d));
}

TEST(Point3DEqualTest, HandlesEqual) {
    Point3D a(1.0f, -2.000099f, 2.0f);
    Point3D b(1.0f, -2.0f, 2.0f);
    Point3D c(1.0f, -2.0f, 1.999999f);
    EXPECT_TRUE(a.equal(b));
    EXPECT_TRUE(a.equal(c));
    EXPECT_TRUE(b.equal(c));
}


//Triangle2D tests
TEST(Triangle2DProjection, HandlesNonZeroVertices) {
    Point3D v1(1.0f, 1.0f, 1.0f);
    Point3D v2(-2.0f, -2.0f, 2.0f);
    Point3D v3(3.0f, 3.0f, -3.0f);
    Triangle3D t(v1, v2, v3);

    Triangle2D a0(t, 0);
    Point2D a00(1.0f, 1.0f);
    Point2D a01(-2.0f, 2.0f);
    Point2D a02(3.0f, -3.0f);
    Triangle2D a1(a00, a01, a02);

    Triangle2D b0(t, 1);
    Point2D b00(1.0f, 1.0f);
    Point2D b01(-2.0f, 2.0f);
    Point2D b02(3.0f, -3.0f);
    Triangle2D b1(b00, b01, b02);

    Triangle2D c0(t, 2);
    Point2D c00(1.0f, 1.0f);
    Point2D c01(-2.0f, -2.0f);
    Point2D c02(3.0f, 3.0f);
    Triangle2D c1(c00, c01, c02);

    EXPECT_TRUE(a0.equal(a1));
    EXPECT_TRUE(b0.equal(b1));
    EXPECT_TRUE(c0.equal(c1));
}

TEST(Triangle2DValid, HandlesValid) {
    Point2D a(1.0f, 1.0f);
    Point2D b(-2.5f, 1.5f);
    Point2D c(3.0f, -3.0f);
    Point2D d(0.0f, 0.0f);

    Triangle2D e(a, b, c);
    Triangle2D f(a, b, d);
    Triangle2D g(a, c, d);
    Triangle2D h(b, c, d);

    EXPECT_TRUE(e.valid());
    EXPECT_TRUE(f.valid());
    EXPECT_TRUE(g.valid());
    EXPECT_TRUE(h.valid());
}

TEST(Triangle2DValid, HandlesNonValid) {
    Point2D a(1.0f, 1.0f);
    Point2D b(2.0f, 2.0f);
    Point2D c(-3.0f, -3.0f);
    Point2D d(0.0f, 0.0f);

    Triangle2D e(a, b, c);
    Triangle2D f(a, b, d);
    Triangle2D g(a, c, d);
    Triangle2D h(b, c, d);

    EXPECT_FALSE(e.valid());
    EXPECT_FALSE(f.valid());
    EXPECT_FALSE(g.valid());
    EXPECT_FALSE(h.valid());
}

//TODO
///Triangle3D tests
// TEST(Triangle3DCopyAndRearrange, HandlesAll) {
//     Point3D a(-1.0f, 1.0f, 1.0f);
//     Point3D b(2.0f, -2.0f, 2.0f);
//     Point3D c(3.0f, 3.0f, -3.0f);
//     Triangle3D t(a, b, c);
//     std::vector<Point3D> v;
//     std::vector<float> sd1 = {1.0f, 1.0f, -1.0f};
//     std::vector<float> sd2 = {1.0f, -1.0f, 1.0f};
//     std::vector<float> sd3 = {-1.0f, 1.0f, 1.0f};
//     std::vector<Point3D> v1 = {a, b, c};
//     std::vector<Point3D> v2 = {a, c, b};
//     std::vector<Point3D> v3 = {c, b, a};

//     t.print();
//     v.clear();
//     t.copy_and_rearrange(v, sd1);
//     for (int i=0; i<3; i++) {
//         v1[i].print();
//         //EXPECT_TRUE(v[i].equal(v1[i]));
//     }

//     v.clear();
//     t.copy_and_rearrange(v, sd2);
//     for (int i=0; i<3; i++) {
//         v2[i].print();
//         //EXPECT_TRUE(v[i].equal(v2[i]));
//     }


//     v.clear();
//     t.copy_and_rearrange(v, sd3);
//     for (int i=0; i<3; i++) {
//         v3[i].print();
//         //EXPECT_TRUE(v[i].equal(v3[i]));
//     }

// }

TEST(Triangle3DValid, HandlesValid) {
    Point3D a(1.0f, 1.0f, 1.0f);
    Point3D b(-2.0f, 2.0f, 2.0f);
    Point3D c(3.0f, -3.0f, 3.0f);
    Point3D d(0.0f, 0.0f, -3.0f);

    Triangle3D e(a, b, c);
    Triangle3D f(a, b, d);
    Triangle3D g(a, c, d);
    Triangle3D h(b, c, d);

    EXPECT_TRUE(e.valid());
    EXPECT_TRUE(f.valid());
    EXPECT_TRUE(g.valid());
    EXPECT_TRUE(h.valid());
}

TEST(Triangle3DValid, HandlesNonValid) {
    Point3D a(1.0f, 1.0f, 1.0f);
    Point3D b(2.0f, 2.0f, 2.0f);
    Point3D c(-3.0f, -3.0f, -3.0f);
    Point3D d(0.0f, 0.0f, 0.0f);

    Triangle3D e(a, b, c);
    Triangle3D f(a, b, d);
    Triangle3D g(a, c, d);
    Triangle3D h(b, c, d);

    EXPECT_FALSE(e.valid());
    EXPECT_FALSE(f.valid());
    EXPECT_FALSE(g.valid());
    EXPECT_FALSE(h.valid());
}


//Plane3D tests
TEST(Plane3DFromTriangle, HandlesAll) {
    Point3D v1(1.0f, 0.0f, 0.0f);
    Point3D v2(0.0f, 1.0f, 0.0f);
    Point3D v3(0.0f, 0.0f, 1.0f);
    Triangle3D t(v1, v2, v3);

    Plane3D p(t);
    Plane3D p1(1.0f, 1.0f, 1.0f, -1.0f);

    EXPECT_TRUE(p.coplanar(p1));
    EXPECT_TRUE(p.equal(p1));
}

TEST(Plane3DNearAxis, HandlesAll) {
    Plane3D a(1.0f, 2.0f, 3.0f, 1.0f);
    Plane3D b(3.0f, 2.0f, 1.0f, 2.0f);
    Plane3D c(2.0f, 3.0f, 3.0f, 3.0f);
    Plane3D d(1.0f, 2.0f, 1.0f, 4.0f);
    Plane3D e(1.0f, 1.0f, 1.0f, 5.0f);

    EXPECT_EQ(a.nearly_oriented_axis(), 2);
    EXPECT_EQ(b.nearly_oriented_axis(), 0);
    EXPECT_EQ(c.nearly_oriented_axis(), 1);
    EXPECT_EQ(d.nearly_oriented_axis(), 1);
    EXPECT_EQ(e.nearly_oriented_axis(), 0);
}

TEST(Plane3DCoplanar, HandlesCoplanar) {
    Plane3D a(1.0f, 2.0f, 3.0f, 1.0f);
    Plane3D b(2.0f, 4.0f, 6.0f, 2.0f);
    Plane3D c(-0.5f, -1.0f, -1.5f, -0.5f);

    EXPECT_TRUE(a.coplanar(b));
    EXPECT_TRUE(b.coplanar(c));
    EXPECT_TRUE(a.coplanar(c));
}

TEST(Plane3DCoplanar, HandlesNonCoplanar) {
    Plane3D a(1.0f, 2.0f, 4.0f, 1.0f);
    Plane3D b(2.0f, 4.0f, 6.0f, 2.0f);
    Plane3D c(-0.5f, -6.0f, -1.5f, -0.5f);

    EXPECT_FALSE(a.coplanar(b));
    EXPECT_FALSE(b.coplanar(c));
    EXPECT_FALSE(a.coplanar(c));
}


//Line3D tests
TEST(Line3DLineFrom2Planes, HandlesAll) {
    Plane3D pl1(1.0f, 1.0f, 1.0f, -1.0f);
    Plane3D pl2(-1.0f, -1.0f, 1.0f, -1.0f);
    Plane3D pl3(0.0f, 1.0f, 1.0f, 1.0f);
    Line3D l11(pl1, pl2);
    Line3D l12(pl2, pl3);
    Line3D l13(pl1, pl3);

    Point3D p1(0.0f, 0.0f, 1.0f);
    Point3D d1(2.0f, -2.0f, 0.0f);
    Point3D p2(-0.333f, -0.833f, -0.167f);
    Point3D d2(-2.0f, 1.0f, -1.0f);
    Point3D p3(2.0f, -0.5f, -0.5f);
    Point3D d3(0.0f, -1.0f, 1.0f);
    Line3D l21(p1, d1);
    Line3D l22(p2, d2);
    Line3D l23(p3, d3);

    EXPECT_TRUE(l11.equal(l21));
    EXPECT_TRUE(l12.equal(l22));
    EXPECT_TRUE(l13.equal(l23));
}


//Dot product tests
TEST(DotProduct, HandlesPerpendicular) {
    Point3D a(1.0f, 2.0f, 1.0f);
    Point3D b(-2.0f, 1.0f, 0.0f);

    EXPECT_EQ(dot(a, b), 0.0f);
}

TEST(DotProduct, HandlesAll) {
    Point3D a(1.0f, 2.0f, 3.0f);
    Point3D b(2.0f, 4.0f, 6.0f);
    Point3D c(-0.5f, -1.0f, -1.5f);

    EXPECT_EQ(dot(a, b), 28.0f);
    EXPECT_EQ(dot(b, c), -14.0f);
    EXPECT_EQ(dot(a, c), -7.0f);
}


//Cross product tests
TEST(CrossProduct, HandlesCollinear) {
    Vector3D a(1.0f, 2.0f, 3.0f);
    Vector3D b(-0.5f, -1.0f, -1.5f);

    Vector3D prod;
    cross(prod, a, b);
    Vector3D c(0.0f, 0.0f, 0.0f);

    EXPECT_TRUE(c.equal(prod));
}

TEST(CrossProduct, HandlesAll) {
    Vector3D a(2.0f, 1.0f, -3.0f);
    Vector3D b(0.0f, -1.0f, 1.0f);

    Vector3D prod;
    cross(prod, a, b);
    Vector3D c(-2.0f, -2.0f, -2.0f);

    EXPECT_TRUE(c.equal(prod));
}


//3D distance tests
TEST(Distance3D, HandlesAll) {
    Point3D a(1.0f, 1.0f, 2.0f);
    Point3D b(4.0f, 5.0f, 2.0f);

    EXPECT_EQ(dist3D(a, b), 5.0f);
} 


//Signed distances tests
TEST(SignedDistances, HanledAll) {
    std::vector<float> sd1;
    Point3D v1(1.0f, 1.0f, 1.0f);
    Point3D v2(-1.0f, 0.0f, 0.0f);
    Point3D v3(0.0f, -1.0f, 0.0f);
    Triangle3D t(v1, v2, v3);
    Plane3D p(1.0f, 1.0f, 1.0f, -1.0f);

    std::vector<float> sd2{2, -2, -2};
    signed_distances(sd1, t, p);
    EXPECT_EQ(sd1, sd2);
}


//Interval intersection tests
TEST(IntervalIntersection, HandlesAll) {
    std::vector<float> interval1;
    Point3D v1(0.0f, -1.0f, 0.0f);
    Point3D v2(-1.0f, 0.0f, 0.0f);
    Point3D v3(1.0f, 1.0f, 1.0f);
    std::vector<Point3D> v;
    v.push_back(v1);
    v.push_back(v2);
    v.push_back(v3);
    std::vector<float> sd{-2, -2, 2};
    Triangle3D t(v1, v2, v3);
    Plane3D p1(t);
    Plane3D p2(1.0f, 1.0f, 1.0f, -1.0f);
    Line3D l(p1, p2);

    intersection_interval(interval1, v, sd, l);
    std::vector<float> interval2{-2, 2};
    EXPECT_EQ(interval1, interval2);
}


int main(int argc, char* argv[]) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}