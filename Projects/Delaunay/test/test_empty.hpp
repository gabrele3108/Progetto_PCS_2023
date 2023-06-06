#ifndef __TEST_EMPTY_H
#define __TEST_EMPTY_H

#include <gtest/gtest.h>

#include "Delaunay.hpp"

using namespace testing;

TEST(TestPoint, TestConstruction)
{
  ProjectLibrary::Point p = ProjectLibrary::Point(1.0, 2.0, 3) ;
  EXPECT_EQ(p.Show(),"x: 1.0, y: 2.0, id: 3\n");


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
  EXPECT_TRUE(t1.Show() == "This triangle is made of the following 3 points:\n"
                           "p1: x: -1.0, y: 0.0, id: 1\n"
                           "p2: x: 1.0, y: 0.0, id: 2\n"
                           "p3: x: 0.0, y: 1.0, id: 3)\n");

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

   d.manualImportSegs(&segment12);
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

TEST(TestLibraryMethods, TestMaxAreaTriangle)
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
