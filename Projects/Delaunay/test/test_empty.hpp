#ifndef __TEST_EMPTY_H
#define __TEST_EMPTY_H

#include <gtest/gtest.h>

#include "Delaunay.hpp"

using namespace testing;

TEST(TestPoint, TestConstruction)
{
  ProjectLibrary::Point p = ProjectLibrary::Point(1.0, 2.0, 3) ;
  EXPECT_EQ(p.Show(),"x: 1, y: 2, id: 3\n");


}

TEST(TestTriangle, TestCreateTriangle)
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

TEST(TestTriangle, TestGetter)
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
}

TEST(TestLibraryMethods, TestImport)
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

TEST(TestConvexHull, TestThreePoints){
    ProjectLibrary::Point pp1(0.0, 1.0, 1);
    ProjectLibrary::Point pp2(-1.0, 0.0, 2);
    ProjectLibrary::Point pp3(0.0, -1.0, 3);
    vector<ProjectLibrary::Point> points = {pp1,pp2,pp3};
    vector<ProjectLibrary::Point> hull = ProjectLibrary::ConvexHull(points);
    EXPECT_TRUE(hull.size() == 3);
    EXPECT_TRUE(hull[0] == pp2);
    EXPECT_TRUE(hull[1] == pp3);
    EXPECT_TRUE(hull[2] == pp1);
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


/*TEST(TestDelaunay, TestCheckDelaunay){
    ProjectLibrary::Delaunay d;
    ProjectLibrary::Point *p1 = new ProjectLibrary::Point(0,0,1);
    ProjectLibrary::Point *p2 = new ProjectLibrary::Point(1,0,2);
    ProjectLibrary::Point *p3 = new ProjectLibrary::Point(0,4,3);
    ProjectLibrary::Point *p4 = new ProjectLibrary::Point(0,1,4);

    ProjectLibrary::Triangle *t1 = new ProjectLibrary:: Triangle (*p1,*p2,*p3);
    ProjectLibrary::Triangle *t2 = new ProjectLibrary:: Triangle(*p1,*p3,*p4);

    //ProjectLibrary::Delaunay d;

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

    s24->connectTriangle(t1);
    s24->connectTriangle(t2);

    std::queue<ProjectLibrary::Segment*> q;

    q.push(s13);

    d.checkDelaunay(q);

    EXPECT_TRUE(**d.segments.end() == *s24);
}*/




/*TEST(TestLibraryMethods, TestArea)
{
    ProjectLibrary::Point pp1(0, 1, 1);
    ProjectLibrary::Point pp2(-1, 0, 2);
    ProjectLibrary::Point pp3(0, -1, 3);
    ProjectLibrary::Delaunay d;
    d.manualImportPoint(pp1);
    d.manualImportPoint(pp2);
    d.manualImportPoint(pp3);
    EXPECT_TRUE(d.Area(pp1,pp2,pp3) == 1);

}


TEST(TestLibraryMethods, TestIntersect)
{
   ProjectLibrary::Point pp1(0, 1, 1);
   ProjectLibrary::Point pp2(-1, 0, 2);
   ProjectLibrary::Point pp3(0, -1, 3);
   ProjectLibrary::Point pp4(1, 0, 4);
   ProjectLibrary::Delaunay d;
   d.manualImportPoint(pp1);
   d.manualImportPoint(pp2);
   d.manualImportPoint(pp3);
   d.manualImportPoint(pp4);
   EXPECT_FALSE(d.intersect(pp1,pp2,pp3,pp4));
   EXPECT_TRUE(d.intersect(pp1,pp3,pp2,pp4));
}

TEST(TestLibraryMethods,TestIntersectCommonP)
{
    ProjectLibrary::Point pp1(0, 1, 1);
    ProjectLibrary::Point pp2(-1, 0, 2);
    ProjectLibrary::Point pp3(0, -1, 3);
    ProjectLibrary::Delaunay d;
    d.manualImportPoint(pp1);
    d.manualImportPoint(pp2);
    d.manualImportPoint(pp3);
    EXPECT_TRUE(d.intersect(pp1,pp2,pp2,pp3));
    EXPECT_TRUE(d.intersect(pp2,pp1,pp2,pp3));
}

TEST(TestLibraryMethods, TestImport)
{
    ProjectLibrary::Delaunay d;
    ProjectLibrary::Point p1(0.0,0.0,0);
    ProjectLibrary::Point p2(1.0,0.0,0);
    ProjectLibrary::Point p3(1.0,1.0,0);
    ProjectLibrary::Point p4(0.0,1.0,0);
    d.importMesh("C:/Users/aless/Desktop/PCS/PCS2023_Exercises/Projects/Delaunay/Dataset/importPointsTest.csv");
    EXPECT_TRUE(d.checkPoint(0) == p1);
    EXPECT_TRUE(d.checkPoint(1) == p2);
    EXPECT_TRUE(d.checkPoint(2) == p3);
    EXPECT_TRUE(d.checkPoint(3) == p4);
}

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
}

TEST(TestLibraryMethods, TestCCWColinear)
{
    ProjectLibrary::Delaunay d;
    ProjectLibrary::Point pcol1(0.0,0.0,0);
    ProjectLibrary::Point pcol2(1.0,1.0,1);
    ProjectLibrary::Point pcol3(2.0,2.0,2);

    EXPECT_TRUE(d.ccw(pcol1,pcol2,pcol3));
    EXPECT_TRUE(d.ccw(pcol1,pcol3,pcol2));
    EXPECT_TRUE(d.ccw(pcol3,pcol1,pcol2));

}*/




#endif // __TEST_EMPTY_H
