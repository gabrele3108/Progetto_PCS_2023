#ifndef __TEST_EMPTY_H
#define __TEST_EMPTY_H

#include <gtest/gtest.h>

#include "Delaunay.hpp"

using namespace testing;

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


#endif //__TEST_EMPTY_H
