#ifndef __TEST_EMPTY_H
#define __TEST_EMPTY_H

#include <gtest/gtest.h>

#include "Delaunay.hpp"

using namespace testing;

TEST(TestPoint, TestConstruction)
{
  ProjectLibrary::Point p = ProjectLibrary::Point(1.0, 2.0, 3);
  ProjectLibrary::Point p0 = ProjectLibrary::Point();
  EXPECT_EQ(p.Show(),"x: 1, y: 2, id: 3\n");
  EXPECT_EQ(p0.Show(),"x: 0, y: 0, id: 0\n");

}

TEST(TestPoint, TestOperatorsAbs)
{
  ProjectLibrary::Point p = ProjectLibrary::Point(1.0, 2.0, 1);
  ProjectLibrary::Point pEps = ProjectLibrary::Point(1.0000000000001,2.00000000000001,2);
  EXPECT_TRUE(p == pEps);
  EXPECT_TRUE(p <= pEps);
  EXPECT_FALSE(p != pEps);
  EXPECT_FALSE(p > pEps);

}

TEST(TestPoint, TestOperatorsRel)
{
  ProjectLibrary::Point p = ProjectLibrary::Point(1.0*pow(10,13), 2.0, 1);
  ProjectLibrary::Point pEps = ProjectLibrary::Point(1.0*pow(10,13) + 1,2.00000000000001,2);
  EXPECT_TRUE(p == pEps);
  EXPECT_TRUE(p <= pEps);
  EXPECT_FALSE(p != pEps);
  EXPECT_FALSE(p > pEps);

}










TEST(TestLibraryMethods, TestCCW)
{
    ProjectLibrary::Point pp1(0.0, 0.0, 0);
    ProjectLibrary::Point pp2(1.0, 0.0, 1);
    ProjectLibrary::Point pp3(0.0, 1.0, 2);

    EXPECT_TRUE(ccw(pp1,pp2,pp3));
    EXPECT_TRUE(ccw(pp2,pp3,pp1));
    EXPECT_TRUE(ccw(pp3,pp1,pp2));

    EXPECT_FALSE(ccw(pp1,pp3,pp2));
    EXPECT_FALSE(ccw(pp3,pp2,pp1));
    EXPECT_FALSE(ccw(pp2,pp1,pp3));
}

TEST(TestLibraryMethods, TestCCWColinear)
{
    ProjectLibrary::Point pcol1(0.0, 0.0, 0);
    ProjectLibrary::Point pcol2(1.0, 1.0, 1);
    ProjectLibrary::Point pcol3(2.0, 2.0, 2);

    EXPECT_TRUE(ccw(pcol1,pcol2,pcol3));
    EXPECT_TRUE(ccw(pcol1,pcol3,pcol2));
    EXPECT_TRUE(ccw(pcol2,pcol1,pcol3));
    EXPECT_TRUE(ccw(pcol2,pcol3,pcol1));
    EXPECT_TRUE(ccw(pcol3,pcol1,pcol2));
    EXPECT_TRUE(ccw(pcol3,pcol2,pcol1));

}

TEST(TestLibraryMethods, TestCCWHull)
{
    ProjectLibrary::Point pp1(0.0, 0.0, 0);
    ProjectLibrary::Point pp2(1.0, 0.0, 1);
    ProjectLibrary::Point pp3(0.0, 1.0, 2);

    EXPECT_TRUE(ccwHull(pp1,pp2,pp3));
    EXPECT_TRUE(ccwHull(pp2,pp3,pp1));
    EXPECT_TRUE(ccwHull(pp3,pp1,pp2));

    EXPECT_FALSE(ccwHull(pp1,pp3,pp2));
    EXPECT_FALSE(ccwHull(pp3,pp2,pp1));
    EXPECT_FALSE(ccwHull(pp2,pp1,pp3));
}

TEST(TestLibraryMethods, TestCCWHullColinear)
{
    ProjectLibrary::Point pcol1(0.0, 0.0, 0);
    ProjectLibrary::Point pcol2(1.0, 1.0, 1);
    ProjectLibrary::Point pcol3(2.0, 2.0, 2);

    EXPECT_FALSE(ccwHull(pcol1,pcol2,pcol3));
    EXPECT_TRUE(ccwHull(pcol1,pcol3,pcol2));
    EXPECT_FALSE(ccwHull(pcol2,pcol1,pcol3));
    EXPECT_FALSE(ccwHull(pcol2,pcol3,pcol1));
    EXPECT_FALSE(ccwHull(pcol3,pcol1,pcol2));
    EXPECT_FALSE(ccwHull(pcol3,pcol2,pcol1));

}

TEST(TestLibraryMethods, TestIntersect)
{
   ProjectLibrary::Point pp1(0.0, 1.0, 1);
   ProjectLibrary::Point pp2(-1.0, 0.0, 2);
   ProjectLibrary::Point pp3(0.0, -1.0, 3);
   ProjectLibrary::Point pp4(1.0, 0.0, 4);
   EXPECT_FALSE(intersect(pp1,pp2,pp3,pp4));
   EXPECT_TRUE(intersect(pp1,pp3,pp2,pp4));
}

TEST(TestLibraryMethods, TestIntersectCommVertex)
{
   ProjectLibrary::Point pp1(0.0, 1.0, 1);
   ProjectLibrary::Point pp2(-1.0, 0.0, 2);
   ProjectLibrary::Point pp3(0.0, -1.0, 3);
   EXPECT_FALSE(intersect(pp1,pp2,pp3,pp1));
}

TEST(TestLibraryMethods, TestIntersectParalleliSovrapposti)
{
   ProjectLibrary::Point pp1(0.5, 0.0, 1);
   ProjectLibrary::Point pp2(-0.5, 0, 2);
   ProjectLibrary::Point pp3(0.0, 0.0, 3);
   ProjectLibrary::Point pp4(1.0, 0.0, 4);
   EXPECT_TRUE(intersect(pp1,pp2,pp3,pp4));
}

TEST(TestLibraryMethods, TestIntersectParalleliContenuti)
{
   ProjectLibrary::Point pp1(-1.0, 0.0, 1);
   ProjectLibrary::Point pp2(1.0, 0, 2);
   ProjectLibrary::Point pp3(-0.5, 0.0, 3);
   ProjectLibrary::Point pp4(0.5, 0.0, 4);
   EXPECT_TRUE(intersect(pp1,pp2,pp3,pp4));
}

TEST(TestLibraryMethods, TestIntersectParalleliStaccati)
{
   ProjectLibrary::Point pp1(-1.0, 0.0, 1);
   ProjectLibrary::Point pp2(-0.5, 0.0, 2);
   ProjectLibrary::Point pp3(0.5, 0.0, 3);
   ProjectLibrary::Point pp4(1.0, 0.0, 4);
   EXPECT_FALSE(intersect(pp1,pp2,pp3,pp4));
}

TEST(TestLibraryMethods, TestIntersectParalleliPuntoComune)
{
   ProjectLibrary::Point pp1(0.5, 0.0, 1);
   ProjectLibrary::Point pp2(-0.5, 0.0, 2);
   ProjectLibrary::Point pp3(0.0, 0.0, 3);
   EXPECT_FALSE(intersect(pp1,pp3,pp3,pp2));
}

TEST(TestLibraryMethods, TestIntersectParalleliVerticeComune)
{
   ProjectLibrary::Point pp1(0.5, 0.0, 1);
   ProjectLibrary::Point pp2(1.0, 0.0, 2);
   ProjectLibrary::Point pp3(0.0, 0.0, 3);
   EXPECT_TRUE(intersect(pp1,pp3,pp3,pp2));
}

TEST(TestLibraryMethods, TestIntersectVerticaliSovrapposti)
{
   ProjectLibrary::Point pp1(0.0, 0.5, 1);
   ProjectLibrary::Point pp2(0.0, -0.5, 2);
   ProjectLibrary::Point pp3(0.0, 0.0, 3);
   ProjectLibrary::Point pp4(0.0, 1.0, 4);
   EXPECT_TRUE(intersect(pp1,pp2,pp3,pp4));
}

TEST(TestLibraryMethods, TestIntersectVerticaliContenuti)
{
   ProjectLibrary::Point pp1(0.0, -1.0, 1);
   ProjectLibrary::Point pp2(0.0, 1.0, 2);
   ProjectLibrary::Point pp3(0.0, -0.5, 3);
   ProjectLibrary::Point pp4(0.0, 0.5, 4);
   EXPECT_TRUE(intersect(pp1,pp2,pp3,pp4));
}

TEST(TestLibraryMethods, TestIntersectVerticaliStaccati)
{
   ProjectLibrary::Point pp1(0.0, -1.0, 1);
   ProjectLibrary::Point pp2(0.0, -0.5, 2);
   ProjectLibrary::Point pp3(0.0, 0.5, 3);
   ProjectLibrary::Point pp4(0.0, 1.0, 4);
   EXPECT_FALSE(intersect(pp1,pp2,pp3,pp4));
}

TEST(TestLibraryMethods, TestIntersectVerticaliPuntoComune)
{
   ProjectLibrary::Point pp1(0.0, 0.5, 1);
   ProjectLibrary::Point pp2(0.0, -0.5, 2);
   ProjectLibrary::Point pp3(0.0, 0.0, 3);
   EXPECT_FALSE(intersect(pp1,pp3,pp3,pp2));
}

TEST(TestLibraryMethods, TestIntersectVerticaliVerticeComune)
{
   ProjectLibrary::Point pp1(0.0, 0.5, 1);
   ProjectLibrary::Point pp2(0.0, 1.0, 2);
   ProjectLibrary::Point pp3(0.0, 0.0, 3);
   EXPECT_TRUE(intersect(pp1,pp3,pp3,pp2));
}

TEST(TestLibraryMethods, TestArea)
{
    ProjectLibrary::Point pp1(0.0, 1.0, 1);
    ProjectLibrary::Point pp2(-1.0, 0.0, 2);
    ProjectLibrary::Point pp3(0.0, -1.0, 3);
    EXPECT_TRUE(Area(pp1,pp2,pp3) == 1);
}









TEST(TestSegment, TestConstructor)
{
    ProjectLibrary::Point p1 = ProjectLibrary::Point(0,0,1);
    ProjectLibrary::Point p2 = ProjectLibrary::Point(1,0,2);
    ProjectLibrary::Segment s = ProjectLibrary::Segment(p1,p2);
    EXPECT_EQ(s.Show(),"p1: x: 1, y: 0, id: 2\np2: x: 0, y: 0, id: 1\nIl segmento è adiacente a 0 triangoli\n");
}

TEST(TestSegment, TestConnectAndDisconnect)
{
    ProjectLibrary::Point p1 = ProjectLibrary::Point(1,0,0);
    ProjectLibrary::Point p2 = ProjectLibrary::Point(0,0,1);
    ProjectLibrary::Point p3 = ProjectLibrary::Point(0,1,2);
    ProjectLibrary::Segment s1 = ProjectLibrary::Segment(p1,p2);
    ProjectLibrary::Triangle t = ProjectLibrary::Triangle(p1,p2,p3);

    s1.connectTriangle(&t);
    EXPECT_EQ(s1.c,1);
    s1.disconnectTriangle(&t);
    EXPECT_EQ(s1.c,0);
}

TEST(TestSegment, TestOperators)
{
  ProjectLibrary::Point p1 = ProjectLibrary::Point(1.0, 2.0, 1);
  ProjectLibrary::Point p1Eps = ProjectLibrary::Point(1.0000000000001,2.00000000000001,2);
  ProjectLibrary::Point p2 = ProjectLibrary::Point(2,3,3);
  ProjectLibrary::Segment s1 = ProjectLibrary::Segment(p1,p2);
    ProjectLibrary::Segment s1Eps = ProjectLibrary::Segment(p1Eps,p2);
  EXPECT_TRUE(s1 == s1Eps);
  EXPECT_FALSE(s1 != s1Eps);

}









TEST(TestTriangle, TestConstruction)
{
  ProjectLibrary::Point pp1(-1.0, 0.0, 1) ;
  ProjectLibrary::Point pp2(1.0, 0.0, 2) ;
  ProjectLibrary::Point pp3(0.0, 1.0, 3) ;
  ProjectLibrary::Triangle t1(pp1,pp2,pp3);
  ProjectLibrary::Triangle t2(pp2,pp3,pp1);
  ProjectLibrary::Triangle t3(pp3,pp1,pp2);
  ProjectLibrary::Triangle t4(pp2,pp1,pp3);
  ProjectLibrary::Triangle t5(pp1,pp3,pp2);
  ProjectLibrary::Triangle t6(pp3,pp2,pp1);

  EXPECT_TRUE(t1==t2);
  EXPECT_TRUE(t1==t3);
  EXPECT_TRUE(t1==t4);
  EXPECT_TRUE(t1==t5);
  EXPECT_TRUE(t1==t6);
  EXPECT_EQ(t1.Show(), "This triangle is made of the following 3 points:\np1: x: -1, y: 0, id: 1\n\np2: x: 1, y: 0, id: 2\n\np3: x: 0, y: 1, id: 3\n\n");

}

TEST(TestTriangle, TestSetSegment)
{
  ProjectLibrary::Point pp1(-1.0, 0.0, 1) ;
  ProjectLibrary::Point pp2(1.0, 0.0, 2) ;
  ProjectLibrary::Point pp3(0.0, 1.0, 3) ;
  ProjectLibrary::Triangle t(pp1,pp2,pp3);
  ProjectLibrary::Segment segment12(pp1,pp2);
  ProjectLibrary::Segment segment23(pp2,pp3);
  ProjectLibrary::Segment segment31(pp3,pp1);
  t.setSegment(&segment12);
  t.setSegment(&segment23);
  t.setSegment(&segment31);
  EXPECT_TRUE(*t.segs[0] == segment12);
  EXPECT_TRUE(*t.segs[1] == segment23);
  EXPECT_TRUE(*t.segs[2] == segment31);
}

TEST(TestTriangle, TestThirdPoint)
{
  ProjectLibrary::Point pp1(0.0, 0.0, 0) ;
  ProjectLibrary::Point pp2(1.0, 0.0, 1) ;
  ProjectLibrary::Point pp3(0.0, 1.0, 2) ;
  ProjectLibrary::Triangle t(pp1,pp2,pp3);
  ProjectLibrary::Segment s12(pp1,pp2);
  ProjectLibrary::Segment s23(pp2,pp3);
  ProjectLibrary::Segment s31(pp3,pp1);
  t.setSegment(&s12);
  t.setSegment(&s23);
  t.setSegment(&s31);
  EXPECT_EQ(*t.ThirdPoint(t.segs[0]),pp3);
  EXPECT_EQ(*t.ThirdPoint(t.segs[1]),pp1);
  EXPECT_EQ(*t.ThirdPoint(t.segs[2]),pp2);
}

TEST(TestTriangle, TestInsideOfC)
{
  ProjectLibrary::Point pp1(0.0, 0.0, 1);
  ProjectLibrary::Point pp2(1.0, 0.0, 2);
  ProjectLibrary::Point pp3(0.0, 1.0, 3);
  ProjectLibrary::Triangle t(pp1,pp2,pp3);
  ProjectLibrary::Point point1(0.5, 0.2, 4);
  ProjectLibrary::Point point2(1.5, 1.5, 5);
  EXPECT_FALSE(t.insideOfC(point2));
  EXPECT_TRUE(t.insideOfC(point1));
}

TEST(TestTriangle, TestInsideOfConC)
{
  ProjectLibrary::Point pp1(0.0, 0.0, 1);
  ProjectLibrary::Point pp2(1.0, 0.0, 2);
  ProjectLibrary::Point pp3(0.0, 1.0, 3);
  ProjectLibrary::Triangle t(pp1,pp2,pp3);
  ProjectLibrary::Point point4(1.0, 1.0, 4);
  EXPECT_FALSE(t.insideOfC(point4));
}

TEST(TestTriangle, TestInsideOfT)
{
  ProjectLibrary::Point pp1(0.0, 0.0, 1);
  ProjectLibrary::Point pp2(1.0, 0.0, 2);
  ProjectLibrary::Point pp3(0.0, 1.0, 3);
  ProjectLibrary::Triangle t(pp1,pp2,pp3);
  ProjectLibrary::Point point1(0.5, 0.2, 4);
  ProjectLibrary::Point point2(0.5, 0.7, 5);
  EXPECT_FALSE(t.insideOfT(point2));
  EXPECT_TRUE(t.insideOfT(point1));
}

TEST(TestTriangle, TestInsideOfTBorder)
{
    ProjectLibrary::Point pp1(0.0, 0.0, 0);
    ProjectLibrary::Point pp2(1.0, 0.0, 1);
    ProjectLibrary::Point pp3(0.0, 1.0, 2);
    ProjectLibrary::Point pp4(0.5, 0.5, 3);

    ProjectLibrary::Triangle t(pp1,pp2,pp3);

    EXPECT_TRUE(t.insideOfT(pp4));
}

TEST(TestTriangle, TestInsideOfTVertex)
{
    ProjectLibrary::Point pp1(0.0, 0.0, 0);
    ProjectLibrary::Point pp2(1.0, 0.0, 1);
    ProjectLibrary::Point pp3(0.0, 1.0, 2);
    ProjectLibrary::Point pp4(0.0, 1.0, 3);

    ProjectLibrary::Triangle t(pp1,pp2,pp3);

    EXPECT_TRUE(t.insideOfT(pp4));
}

TEST(TestTriangle, TestNonAdjSeg)
{
  ProjectLibrary::Point pp1(0.0, 0.0, 0);
  ProjectLibrary::Point pp2(1.0, 0.0, 1);
  ProjectLibrary::Point pp3(0.0, 1.0, 2);
  ProjectLibrary::Triangle t(pp1,pp2,pp3);
  ProjectLibrary::Segment segment12(pp1,pp2);
  ProjectLibrary::Segment segment23(pp2,pp3);
  ProjectLibrary::Segment segment31(pp3,pp1);
  ProjectLibrary::Segment *ss1 = nullptr;
  ProjectLibrary::Segment *ss2 = nullptr;
  t.setSegment(&segment12);
  t.setSegment(&segment23);
  t.setSegment(&segment31);
  t.nonAdjSeg(&segment12, ss1, ss2);
  EXPECT_TRUE(((*t.segs[1] == *ss1) && (*t.segs[1] != segment12)) ||
              ((*t.segs[2] == *ss1) && (*t.segs[2] != segment12)));
  EXPECT_TRUE(((*t.segs[1] == *ss2) && (*t.segs[1] != segment12)) ||
              ((*t.segs[2] == *ss2) && (*t.segs[2] != segment12)));
}









TEST(TestConvexHull, TestLessThanThreePoints){
    ProjectLibrary::Point pp1(0.0, 1.0, 1);
    ProjectLibrary::Point pp2(-1.0, 0.0, 2);
    ProjectLibrary::Point pp3(0.0, -1.0, 3);
    vector<ProjectLibrary::Point> points3 = {pp1,pp2,pp3};
    vector<ProjectLibrary::Point> hull3 = ProjectLibrary::ConvexHull(points3);
    EXPECT_TRUE(hull3.size() == 3);
    EXPECT_TRUE(hull3[0] == pp2);
    EXPECT_TRUE(hull3[1] == pp3);
    EXPECT_TRUE(hull3[2] == pp1);
    vector<ProjectLibrary::Point> points2 = {pp1,pp2};
    vector<ProjectLibrary::Point> hull2 = ProjectLibrary::ConvexHull(points2);
    EXPECT_TRUE(hull2.size() == 2);
    EXPECT_TRUE(hull2[0] == pp2);
    EXPECT_TRUE(hull2[1] == pp1);
    vector<ProjectLibrary::Point> points1 = {pp1};
    vector<ProjectLibrary::Point> hull1 = ProjectLibrary::ConvexHull(points1);
    EXPECT_TRUE(hull1.size() == 1);
    EXPECT_TRUE(hull1[0] == pp1);
}

TEST(TestConvexHull, TestXPoints)
{
  unsigned int numPoints = 0;
  vector<ProjectLibrary::Point> points = {ProjectLibrary::Point(2, 2, numPoints++),
                          ProjectLibrary::Point(2.8, 1.7, numPoints++),
                          ProjectLibrary::Point(3, 5, numPoints++),
                          ProjectLibrary::Point(7, 3, numPoints++),
                          ProjectLibrary::Point(7.2, 5, numPoints++),
                          ProjectLibrary::Point(11, 4.3, numPoints++),
                          ProjectLibrary::Point(12, 5.2, numPoints++),
                          ProjectLibrary::Point(14, 3, numPoints++)
                          };

  vector<ProjectLibrary::Point> convexHull = ConvexHull(points);
  EXPECT_TRUE(convexHull.size() == 5);
  EXPECT_TRUE(convexHull[0] == ProjectLibrary::Point(2, 2, numPoints++));
  EXPECT_TRUE(convexHull[1] == ProjectLibrary::Point(2.8, 1.7, numPoints++));
  EXPECT_TRUE(convexHull[2] == ProjectLibrary::Point(14, 3, numPoints++));
  EXPECT_TRUE(convexHull[3] == ProjectLibrary::Point(12, 5.2, numPoints++));
  EXPECT_TRUE(convexHull[4] == ProjectLibrary::Point(3, 5, numPoints++));

}


TEST(TestConvexHull, TestVerticalPoints)
{
  unsigned int numPoints = 0;
  vector<ProjectLibrary::Point> points = {ProjectLibrary::Point(0, 2, numPoints++),
                          ProjectLibrary::Point(0, 1.7, numPoints++),
                          ProjectLibrary::Point(0, 5, numPoints++),
                          ProjectLibrary::Point(0, 3, numPoints++),
                          ProjectLibrary::Point(0, 6, numPoints++),
                          ProjectLibrary::Point(0, 4.3, numPoints++),
                          ProjectLibrary::Point(0, 5.2, numPoints++),
                          ProjectLibrary::Point(0, 3.1, numPoints++)
                          };

  vector<ProjectLibrary::Point> convexHull = ConvexHull(points);
  EXPECT_TRUE(convexHull.size() == 8);
  EXPECT_TRUE(convexHull[1] == ProjectLibrary::Point(0, 6, numPoints++));
  EXPECT_TRUE(convexHull[2] == ProjectLibrary::Point(0, 5.2, numPoints++));
  EXPECT_TRUE(convexHull[3] == ProjectLibrary::Point(0, 5, numPoints++));
  EXPECT_TRUE(convexHull[4] == ProjectLibrary::Point(0, 4.3, numPoints++));
  EXPECT_TRUE(convexHull[5] == ProjectLibrary::Point(0, 3.1, numPoints++));
  EXPECT_TRUE(convexHull[6] == ProjectLibrary::Point(0, 3, numPoints++));
  EXPECT_TRUE(convexHull[7] == ProjectLibrary::Point(0, 2, numPoints++));
  EXPECT_TRUE(convexHull[0] == ProjectLibrary::Point(0, 1.7, numPoints++));

}

TEST(TestConvexHull, TestSmallSquare)
{
  unsigned int numPoints = 0;
  vector<ProjectLibrary::Point> points = {ProjectLibrary::Point(0, 1, numPoints++),
                          ProjectLibrary::Point(1, 1, numPoints++),
                          ProjectLibrary::Point(1, 0, numPoints++),
                          ProjectLibrary::Point(0, 0, numPoints++),
                          ProjectLibrary::Point(0, 0.5, numPoints++),
                          ProjectLibrary::Point(1, 0.5, numPoints++),
                          ProjectLibrary::Point(0.5, 0, numPoints++),
                          ProjectLibrary::Point(0.5, 1, numPoints++)
                          };

  vector<ProjectLibrary::Point> convexHull = ConvexHull(points);
  EXPECT_TRUE(convexHull.size() == 8);
  EXPECT_TRUE(convexHull[0] == ProjectLibrary::Point(0, 0, numPoints++));
  EXPECT_TRUE(convexHull[1] == ProjectLibrary::Point(0.5, 0, numPoints++));
  EXPECT_TRUE(convexHull[2] == ProjectLibrary::Point(1, 0, numPoints++));
  EXPECT_TRUE(convexHull[3] == ProjectLibrary::Point(1, 0.5, numPoints++));
  EXPECT_TRUE(convexHull[4] == ProjectLibrary::Point(1, 1, numPoints++));
  EXPECT_TRUE(convexHull[5] == ProjectLibrary::Point(0.5, 1, numPoints++));
  EXPECT_TRUE(convexHull[6] == ProjectLibrary::Point(0, 1, numPoints++));
  EXPECT_TRUE(convexHull[7] == ProjectLibrary::Point(0, 0.5, numPoints++));

}









TEST(TestDelauney, TestGetSegmentIndex)
{
   ProjectLibrary::Point pp1(0.0, 1.0, 1);
   ProjectLibrary::Point pp2(-1.0, 0.0, 2);
   ProjectLibrary::Point pp3(0.0, -1.0, 3);
   ProjectLibrary::Point pp4(1.0, 1.0, 4);
   ProjectLibrary::Point pp5(-1.0, -1.0, 5);
   ProjectLibrary::Segment segment12(pp1,pp2);
   ProjectLibrary::Segment segment23(pp2,pp3);
   ProjectLibrary::Segment segment34(pp3,pp4);
   ProjectLibrary::Segment segment15(pp1,pp5);
   ProjectLibrary::Segment segment45(pp4,pp5);
   ProjectLibrary::Segment segment24(pp2,pp4);
   ProjectLibrary::Segment segment13(pp1,pp3);
   ProjectLibrary::Delaunay d;
   d.points.push_back(pp1);
   d.points.push_back(pp2);
   d.points.push_back(pp3);
   d.points.push_back(pp4);
   d.points.push_back(pp5);

   d.segments.push_back(&segment12);
   d.segments.push_back(&segment23);
   d.segments.push_back(&segment34);
   d.segments.push_back(&segment15);
   d.segments.push_back(&segment45);
   d.segments.push_back(&segment24);


   unsigned int k = d.getSegmentIndex(pp1,pp5);
   EXPECT_TRUE(*d.segments[k] == segment15);
   k = d.getSegmentIndex(pp1,pp3);
   EXPECT_TRUE(k == d.segments.size());
}

TEST(TestDelaunay, TestImport)
{
    ProjectLibrary::Delaunay d;
    ProjectLibrary::Point p1(0.0,0.0,0);
    ProjectLibrary::Point p2(1.0,0.0,0);
    ProjectLibrary::Point p3(1.0,1.0,0);
    ProjectLibrary::Point p4(0.0,1.0,0);
    d.importMesh("./importPointsTest.csv");
    EXPECT_TRUE(d.points[0] == p1);
    EXPECT_TRUE(d.points[1] == p2);
    EXPECT_TRUE(d.points[2] == p3);
    EXPECT_TRUE(d.points[3] == p4);
}


TEST(TestDelaunay, TestMaxAreaTriangle)
{
    ProjectLibrary::Point pp1(0, 1, 1);
    ProjectLibrary::Point pp2(-1, 0, 2);
    ProjectLibrary::Point pp3(0, -1, 3);
    ProjectLibrary::Point pp4(1, 0, 4);
    ProjectLibrary::Point pp5(1, 1, 5);
    ProjectLibrary::Delaunay d;
    d.points.push_back(pp1);
    d.points.push_back(pp2);
    d.points.push_back(pp3);
    d.points.push_back(pp4);
    d.points.push_back(pp5);
    d.maxAreaTriangle();
    ProjectLibrary::Triangle t(pp2,pp3,pp5);


    EXPECT_TRUE(*d.triangles[0] == t);
}

TEST(TestDelaunay, TestMaxAreaTriangleNSQ)
{
    ProjectLibrary::Point pp1(0, 1, 1);
    ProjectLibrary::Point pp2(-1, 0, 2);
    ProjectLibrary::Point pp3(0, -1, 3);
    ProjectLibrary::Point pp4(1, 0, 4);
    ProjectLibrary::Point pp5(1, 1, 5);
    ProjectLibrary::Delaunay d;
    d.points.push_back(pp1);
    d.points.push_back(pp2);
    d.points.push_back(pp3);
    d.points.push_back(pp4);
    d.points.push_back(pp5);
    d.maxAreaTriangleNSQ();
    ProjectLibrary::Triangle t(pp2,pp3,pp5);


    EXPECT_TRUE(*d.triangles[0] == t);
}


TEST(TestDelaunay, TestCheckDelaunay){
    ProjectLibrary::Delaunay d;
    ProjectLibrary::Point *p1 = new ProjectLibrary::Point(0,0,1);
    ProjectLibrary::Point *p2 = new ProjectLibrary::Point(1,0,2);
    ProjectLibrary::Point *p3 = new ProjectLibrary::Point(0,4,3);
    ProjectLibrary::Point *p4 = new ProjectLibrary::Point(0,1,4);

    ProjectLibrary::Triangle *t1 = new ProjectLibrary:: Triangle (*p1,*p2,*p3);
    ProjectLibrary::Triangle *t2 = new ProjectLibrary:: Triangle(*p1,*p3,*p4);


    ProjectLibrary::Segment *s12 = new ProjectLibrary::Segment(*p1,*p2);
    ProjectLibrary::Segment *s14 = new ProjectLibrary::Segment(*p1,*p4);
    ProjectLibrary::Segment *s23 = new ProjectLibrary::Segment(*p2,*p3);
    ProjectLibrary::Segment *s34 = new ProjectLibrary::Segment(*p3,*p4);
    ProjectLibrary::Segment *s13 = new ProjectLibrary::Segment(*p1,*p3);
    ProjectLibrary::Segment *s24 = new ProjectLibrary::Segment(*p2,*p4);

    t1->setSegment(s12);
    t1->setSegment(s23);
    t1->setSegment(s13);

    t2->setSegment(s13);
    t2->setSegment(s34);
    t2->setSegment(s14);

    s13->connectTriangle(t1);
    s12->connectTriangle(t1);
    s23->connectTriangle(t1);
    s13->connectTriangle(t2);
    s34->connectTriangle(t2);
    s14->connectTriangle(t2);

    d.segments.push_back(s12);d.segments.push_back(s23);d.segments.push_back(s13);
    d.segments.push_back(s14);d.segments.push_back(s34);
    d.triangles.push_back(t1);d.triangles.push_back(t2);

    std::queue<ProjectLibrary::Segment*> q;

    q.push(s13);

    d.checkDelaunay(q);

    EXPECT_TRUE(*d.segments[4] == *s24);
}

/*

TEST(TestLibraryMethods, TestTriangulateNoFlip)
{
    ProjectLibrary::Delaunay d;
    ProjectLibrary::Point p1(0.0,0.0,0);
    ProjectLibrary::Point p2(3.0,0.0,0);
    ProjectLibrary::Point p3(0.0,3.0,0);
    ProjectLibrary::Point p4(1.0,-1.0,0);

    d.manualImportPoint(p1);
    d.manualImportPoint(p2);
    d.manualImportPoint(p3);
    d.manualImportPoint(p4);

    d.triangulate();

    EXPECT_TRUE(d.manualExportPoints().size()==4);
    EXPECT_TRUE(d.manualExportSegs().size()==5);
    EXPECT_TRUE(d.manualExportTriang().size()==2);
}*/




#endif // __TEST_EMPTY_H
