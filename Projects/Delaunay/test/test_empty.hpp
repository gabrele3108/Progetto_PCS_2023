#ifndef __TEST_EMPTY_H
#define __TEST_EMPTY_H

#include <gtest/gtest.h>

#include "Delaunay.hpp"

using namespace testing;

TEST(TestPoint, TestGet)
{
  ProjectLibrary::Point p = ProjectLibrary::Point(1, 2, 3) ;
  EXPECT_EQ(p.getX(), 1);
  EXPECT_EQ(p.getY(), 2);
  EXPECT_EQ(p.getID(), 3);

}

TEST(TestTriangle, TestCreateTriangle)
{
  ProjectLibrary::Point pp1(0, 0, 1) ;
  ProjectLibrary::Point pp2(1, 0, 2) ;
  ProjectLibrary::Point pp3(0, 1, 3) ;
  ProjectLibrary::Triangle t1(pp1,pp2,pp3);
  EXPECT_TRUE(t1.getP1() == pp1);
  EXPECT_TRUE(t1.getP2() == pp2);
  EXPECT_TRUE(t1.getP3() ==  pp3);
  ProjectLibrary::Triangle t2(pp1,pp2,pp3);
  EXPECT_TRUE(t2.getP1() ==  pp1);
  EXPECT_TRUE(t2.getP2() == pp2);
  EXPECT_TRUE(t2.getP3() == pp3);
}

TEST(TestTriangle, TestInsideOfC)
{
  ProjectLibrary::Point pp1(0, 0, 1);
  ProjectLibrary::Point pp2(1, 0, 2);
  ProjectLibrary::Point pp3(0, 1, 3);
  ProjectLibrary::Triangle t(pp1,pp2,pp3);
  ProjectLibrary::Point point1(0.5, 0.2, 4);
  ProjectLibrary::Point point2(1.5, 1.5, 5);
  EXPECT_FALSE(t.insideOfC(point2));
  EXPECT_TRUE(t.insideOfC(point1));
}


TEST(TestTriangle, TestInsideOfT)
{
  ProjectLibrary::Point pp1(0, 0, 1);
  ProjectLibrary::Point pp2(1, 0, 2);
  ProjectLibrary::Point pp3(0, 1, 3);
  ProjectLibrary::Triangle t(pp1,pp2,pp3);
  ProjectLibrary::Point point1(0.5, 0.2, 4);
  ProjectLibrary::Point point2(0.5, 0.7, 5);
  EXPECT_FALSE(t.insideOfT(point2));
  EXPECT_TRUE(t.insideOfT(point1));
}

TEST(TestTriangle, TestInsideOfTBorder)
{
    ProjectLibrary::Point piob1(0.0,0.0,0);
    ProjectLibrary::Point piob2(1.0,1.0,1);
    ProjectLibrary::Point piob3(2.0,2.0,2);
    ProjectLibrary::Point piob4(2.0,0.0,3);

    ProjectLibrary::Triangle t1(piob1,piob3,piob4);

    EXPECT_TRUE(t1.insideOfT(piob2));
}

TEST(TestDelaunay, TestMaxAreaTriangle)
{
    ProjectLibrary::Point pp1(0, 1, 1);
    ProjectLibrary::Point pp2(-1, 0, 2);
    ProjectLibrary::Point pp3(0, -1, 3);
    ProjectLibrary::Point pp4(1, 0, 4);
    ProjectLibrary::Point pp5(1, 1, 5);
    ProjectLibrary::Delaunay d;
    d.manualImportPoint(pp1);
    d.manualImportPoint(pp2);
    d.manualImportPoint(pp3);
    d.manualImportPoint(pp4);
    d.manualImportPoint(pp5);
    d.maxAreaTriangle();
    ProjectLibrary::Triangle t(pp2,pp3,pp5);

    /*EXPECT_TRUE(d.triangles.begin().getP1() == t.getP1() &&
                d.triangles.begin().getP2() == t.getP2() &&
                d.triangles.begin().getP3() == t.getP3());*/

    EXPECT_TRUE(d.checkTriangle(0) == t);
}


TEST(TestDelaunay, TestArea)
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

TEST(TestDelaunay, TestIntersect)
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

TEST(TestDelaunay,TestIntersectCommonP)
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

TEST(TestDelaunay, TestImport)
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

TEST(TestDelaunay, TestTriangulateNoFlip)
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

TEST(TestDelaunay, TestCCWColinear)
{
    ProjectLibrary::Delaunay d;
    ProjectLibrary::Point pcol1(0.0,0.0,0);
    ProjectLibrary::Point pcol2(1.0,1.0,1);
    ProjectLibrary::Point pcol3(2.0,2.0,2);

    EXPECT_TRUE(d.ccw(pcol1,pcol2,pcol3));
    EXPECT_TRUE(d.ccw(pcol1,pcol3,pcol2));
    EXPECT_TRUE(d.ccw(pcol3,pcol1,pcol2));

}




#endif // __TEST_EMPTY_H
