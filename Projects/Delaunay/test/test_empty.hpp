#ifndef __TEST_EMPTY_H
#define __TEST_EMPTY_H

#include <gtest/gtest.h>

#include "Delaunay.hpp"

using namespace testing;

TEST(TestPoint, TestGet)
{
  ProjectLibrary::Point p = ProjectLibrary::Point(1.0, 2.0, 3) ;
  EXPECT_EQ(p.getX(), 1.0);
  EXPECT_EQ(p.getY(), 2.0);
  EXPECT_EQ(p.getID(), 3);

}

TEST(TestTriangle, TestCreateTriangle)
{
  ProjectLibrary::Point pp1(-1.0, 0.0, 1) ;
  ProjectLibrary::Point pp2(1.0, 0.0, 2) ;
  ProjectLibrary::Point pp3(0.0, 1.0, 3) ;
  ProjectLibrary::Triangle t1(pp1,pp2,pp3);
  EXPECT_TRUE(t1.getP1() == pp1);
  EXPECT_TRUE(t1.getP2() == pp2);
  EXPECT_TRUE(t1.getP3() ==  pp3);
  ProjectLibrary::Triangle t2(pp2,pp3,pp1);
  EXPECT_TRUE(t2.getP1() == pp1);
  EXPECT_TRUE(t2.getP2() == pp2);
  EXPECT_TRUE(t2.getP3() ==  pp3);
  ProjectLibrary::Triangle t3(pp3,pp1,pp2);
  EXPECT_TRUE(t3.getP1() == pp1);
  EXPECT_TRUE(t3.getP2() == pp2);
  EXPECT_TRUE(t3.getP3() ==  pp3);
  ProjectLibrary::Triangle t4(pp2,pp1,pp3);
  EXPECT_TRUE(t4.getP1() ==  pp1);
  EXPECT_TRUE(t4.getP2() == pp2);
  EXPECT_TRUE(t4.getP3() == pp3);
}

TEST(TestTriangle, TestGetter)
{
  ProjectLibrary::Point pp1(-1.0, 0.0, 1) ;
  ProjectLibrary::Point pp2(1.0, 0.0, 2) ;
  ProjectLibrary::Point pp3(0.0, 1.0, 3) ;
  ProjectLibrary::Triangle t(pp1,pp2,pp3);
  ProjectLibrary::Segment segment12(pp1,pp2);
  t.setS1(&segment12);
  ProjectLibrary::Segment segment23(pp2,pp3);
  t.setS2(&segment23);
  ProjectLibrary::Segment segment31(pp3,pp1);
<<<<<<< HEAD
  t.setS3(&segment31);
=======
  t.setSegment(&segment12);
  t.setSegment(&segment23);
  t.setSegment(&segment31);
>>>>>>> 1aad896841fa7adde99be503850ce87bb2da282b
  EXPECT_TRUE(*t.getS1() == segment12);
  EXPECT_TRUE(*t.getS2() == segment23);
  EXPECT_TRUE(*t.getS3() == segment31);
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
  EXPECT_EQ(*t.ThirdPoint(t.getS1()),pp3);
  EXPECT_EQ(*t.ThirdPoint(t.getS2()),pp1);
  EXPECT_EQ(*t.ThirdPoint(t.getS3()),pp2);
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
  EXPECT_TRUE(((*t.getS2() == *ss1) && (*t.getS2() != segment12)) ||
              ((*t.getS3() == *ss1) && (*t.getS3() != segment12)));
  EXPECT_TRUE(((*t.getS2() == *ss2) && (*t.getS2() != segment12)) ||
              ((*t.getS3() == *ss2) && (*t.getS3() != segment12)));
}

TEST(TestTriangle, TestArea)
{
    ProjectLibrary::Point pp1(0.0, 1.0, 1);
    ProjectLibrary::Point pp2(-1.0, 0.0, 2);
    ProjectLibrary::Point pp3(0.0, -1.0, 3);
    ProjectLibrary::Triangle t(pp1,pp2,pp3);
    EXPECT_TRUE(t.Area() == 1.0);
}

TEST(TestDelaunay, TestCCW)
{
    ProjectLibrary::Delaunay d;
    ProjectLibrary::Point pp1(0.0, 0.0, 0);
    ProjectLibrary::Point pp2(1.0, 0.0, 1);
    ProjectLibrary::Point pp3(0.0, 1.0, 2);

    EXPECT_TRUE(d.ccw(pp1,pp2,pp3));
    EXPECT_TRUE(d.ccw(pp2,pp3,pp1));
    EXPECT_TRUE(d.ccw(pp3,pp1,pp2));

    EXPECT_FALSE(d.ccw(pp1,pp3,pp2));
    EXPECT_FALSE(d.ccw(pp3,pp2,pp1));
    EXPECT_FALSE(d.ccw(pp2,pp1,pp3));
<<<<<<< HEAD

=======
>>>>>>> 1aad896841fa7adde99be503850ce87bb2da282b
}

TEST(TestDelaunay, TestCCWColinear)
{
    ProjectLibrary::Delaunay d;
    ProjectLibrary::Point pcol1(0.0, 0.0, 0);
    ProjectLibrary::Point pcol2(1.0, 1.0, 1);
    ProjectLibrary::Point pcol3(2.0, 2.0, 2);

    EXPECT_TRUE(d.ccw(pcol1,pcol2,pcol3));
    EXPECT_TRUE(d.ccw(pcol1,pcol3,pcol2));
    EXPECT_TRUE(d.ccw(pcol2,pcol1,pcol3));
    EXPECT_TRUE(d.ccw(pcol2,pcol3,pcol1));
    EXPECT_TRUE(d.ccw(pcol3,pcol1,pcol2));
    EXPECT_TRUE(d.ccw(pcol3,pcol2,pcol1));

}

TEST(TestDelaunay, TestIntersect)
{
   ProjectLibrary::Point pp1(0.0, 1.0, 1);
   ProjectLibrary::Point pp2(-1.0, 0.0, 2);
   ProjectLibrary::Point pp3(0.0, -1.0, 3);
   ProjectLibrary::Point pp4(1.0, 0.0, 4);
   ProjectLibrary::Delaunay d;
   d.manualImportPoint(pp1);
   d.manualImportPoint(pp2);
   d.manualImportPoint(pp3);
   d.manualImportPoint(pp4);
   EXPECT_FALSE(d.intersect(pp1,pp2,pp3,pp4));
   EXPECT_TRUE(d.intersect(pp1,pp3,pp2,pp4));
}

TEST(TestDelaunay, TestIntersectCommVertex)
{
   ProjectLibrary::Point pp1(0.0, 1.0, 1);
   ProjectLibrary::Point pp2(-1.0, 0.0, 2);
   ProjectLibrary::Point pp3(0.0, -1.0, 3);
   ProjectLibrary::Delaunay d;
   d.manualImportPoint(pp1);
   d.manualImportPoint(pp2);
   d.manualImportPoint(pp3);
   EXPECT_FALSE(d.intersect(pp1,pp2,pp3,pp1));
}

TEST(TestDelaunay, TestIntersectParalleliSovrapposti)
{
   ProjectLibrary::Point pp1(0.5, 0.0, 1);
   ProjectLibrary::Point pp2(-0.5, 0, 2);
   ProjectLibrary::Point pp3(0.0, 0.0, 3);
   ProjectLibrary::Point pp4(1.0, 0.0, 4);
   ProjectLibrary::Delaunay d;
   d.manualImportPoint(pp1);
   d.manualImportPoint(pp2);
   d.manualImportPoint(pp3);
   d.manualImportPoint(pp4);
   EXPECT_TRUE(d.intersect(pp1,pp2,pp3,pp4));
}

TEST(TestDelaunay, TestIntersectParalleliContenuti)
{
   ProjectLibrary::Point pp1(-1.0, 0.0, 1);
   ProjectLibrary::Point pp2(1.0, 0, 2);
   ProjectLibrary::Point pp3(-0.5, 0.0, 3);
   ProjectLibrary::Point pp4(0.5, 0.0, 4);
   ProjectLibrary::Delaunay d;
   d.manualImportPoint(pp1);
   d.manualImportPoint(pp2);
   d.manualImportPoint(pp3);
   d.manualImportPoint(pp4);
   EXPECT_TRUE(d.intersect(pp1,pp2,pp3,pp4));
}

TEST(TestDelaunay, TestIntersectParalleliStaccati)
{
   ProjectLibrary::Point pp1(-1.0, 0.0, 1);
   ProjectLibrary::Point pp2(-0.5, 0.0, 2);
   ProjectLibrary::Point pp3(0.5, 0.0, 3);
   ProjectLibrary::Point pp4(1.0, 0.0, 4);
   ProjectLibrary::Delaunay d;
   d.manualImportPoint(pp1);
   d.manualImportPoint(pp2);
   d.manualImportPoint(pp3);
   d.manualImportPoint(pp4);
   EXPECT_FALSE(d.intersect(pp1,pp2,pp3,pp4));
}

TEST(TestDelaunay, TestIntersectParalleliPuntoComune)
{
   ProjectLibrary::Point pp1(0.5, 0.0, 1);
   ProjectLibrary::Point pp2(-0.5, 0.0, 2);
   ProjectLibrary::Point pp3(0.0, 0.0, 3);
   ProjectLibrary::Delaunay d;
   d.manualImportPoint(pp1);
   d.manualImportPoint(pp2);
   d.manualImportPoint(pp3);
   EXPECT_FALSE(d.intersect(pp1,pp3,pp3,pp2));
}

TEST(TestDelaunay, TestIntersectParalleliVerticeComune)
{
   ProjectLibrary::Point pp1(0.5, 0.0, 1);
   ProjectLibrary::Point pp2(1.0, 0.0, 2);
   ProjectLibrary::Point pp3(0.0, 0.0, 3);
   ProjectLibrary::Delaunay d;
   d.manualImportPoint(pp1);
   d.manualImportPoint(pp2);
   d.manualImportPoint(pp3);
   EXPECT_TRUE(d.intersect(pp1,pp3,pp3,pp2));
}

TEST(TestDelaunay, TestIntersectVerticaliSovrapposti)
{
   ProjectLibrary::Point pp1(0.0, 0.5, 1);
   ProjectLibrary::Point pp2(0.0, -0.5, 2);
   ProjectLibrary::Point pp3(0.0, 0.0, 3);
   ProjectLibrary::Point pp4(0.0, 1.0, 4);
   ProjectLibrary::Delaunay d;
   d.manualImportPoint(pp1);
   d.manualImportPoint(pp2);
   d.manualImportPoint(pp3);
   d.manualImportPoint(pp4);
   EXPECT_TRUE(d.intersect(pp1,pp2,pp3,pp4));
}

TEST(TestDelaunay, TestIntersectVerticaliContenuti)
{
   ProjectLibrary::Point pp1(0.0, -1.0, 1);
   ProjectLibrary::Point pp2(0.0, 1.0, 2);
   ProjectLibrary::Point pp3(0.0, -0.5, 3);
   ProjectLibrary::Point pp4(0.0, 0.5, 4);
   ProjectLibrary::Delaunay d;
   d.manualImportPoint(pp1);
   d.manualImportPoint(pp2);
   d.manualImportPoint(pp3);
   d.manualImportPoint(pp4);
   EXPECT_TRUE(d.intersect(pp1,pp2,pp3,pp4));
}

TEST(TestDelaunay, TestIntersectVerticaliStaccati)
{
   ProjectLibrary::Point pp1(0.0, -1.0, 1);
   ProjectLibrary::Point pp2(0.0, -0.5, 2);
   ProjectLibrary::Point pp3(0.0, 0.5, 3);
   ProjectLibrary::Point pp4(0.0, 1.0, 4);
   ProjectLibrary::Delaunay d;
   d.manualImportPoint(pp1);
   d.manualImportPoint(pp2);
   d.manualImportPoint(pp3);
   d.manualImportPoint(pp4);
   EXPECT_FALSE(d.intersect(pp1,pp2,pp3,pp4));
}

TEST(TestDelaunay, TestIntersectVerticaliPuntoComune)
{
   ProjectLibrary::Point pp1(0.0, 0.5, 1);
   ProjectLibrary::Point pp2(0.0, -0.5, 2);
   ProjectLibrary::Point pp3(0.0, 0.0, 3);
   ProjectLibrary::Delaunay d;
   d.manualImportPoint(pp1);
   d.manualImportPoint(pp2);
   d.manualImportPoint(pp3);
   EXPECT_FALSE(d.intersect(pp1,pp3,pp3,pp2));
}

TEST(TestDelaunay, TestIntersectVerticaliVerticeComune)
{
   ProjectLibrary::Point pp1(0.0, 0.5, 1);
   ProjectLibrary::Point pp2(0.0, 1.0, 2);
   ProjectLibrary::Point pp3(0.0, 0.0, 3);
   ProjectLibrary::Delaunay d;
   d.manualImportPoint(pp1);
   d.manualImportPoint(pp2);
   d.manualImportPoint(pp3);
   EXPECT_TRUE(d.intersect(pp1,pp3,pp3,pp2));
}

TEST(TestDelaunay, TestArea)
{
    ProjectLibrary::Point pp1(0.0, 1.0, 1);
    ProjectLibrary::Point pp2(-1.0, 0.0, 2);
    ProjectLibrary::Point pp3(0.0, -1.0, 3);
    ProjectLibrary::Delaunay d;
    d.manualImportPoint(pp1);
    d.manualImportPoint(pp2);
    d.manualImportPoint(pp3);
    EXPECT_TRUE(d.Area(pp1,pp2,pp3) == 1);
}

/*TEST(TestDelauney, TestGetSegmentIndex)
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
   d.manualImportPoint(pp1);
   d.manualImportPoint(pp2);
   d.manualImportPoint(pp3);
   d.manualImportPoint(pp4);
   d.manualImportPoint(pp5);

   /*d.manualImportSegs(&segment12);
   d.manualImportSegs(&segment23);
   d.manualImportSegs(&segment34);
   d.manualImportSegs(&segment15);
   d.manualImportSegs(&segment45);
   d.manualImportSegs(&segment24);

   (d.manualExportSegs()).push_back(&segment12);
   (d.manualExportSegs()).push_back(&segment23);
   (d.manualExportSegs()).push_back(&segment34);
   (d.manualExportSegs()).push_back(&segment15);
   (d.manualExportSegs()).push_back(&segment45);
   (d.manualExportSegs()).push_back(&segment24);


   unsigned int k = d.getSegmentIndex(pp1,pp5);
   EXPECT_TRUE(*d.manualExportSegs()[k] == segment15);
}*/




/*TEST(TestDelaunay, TestArea)
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


    EXPECT_TRUE(d.checkTriangle(0) == t);
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

}*/




#endif // __TEST_EMPTY_H
