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
