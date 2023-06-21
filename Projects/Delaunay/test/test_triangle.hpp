#ifndef __TEST_EMPTY_H
#define __TEST_EMPTY_H

#include <gtest/gtest.h>

#include "Delaunay.hpp"

using namespace testing;

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

#endif // __TEST_EMPTY_H
