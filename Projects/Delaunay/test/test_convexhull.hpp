#ifndef __TEST_EMPTY_H
#define __TEST_EMPTY_H

#include <gtest/gtest.h>

#include "Delaunay.hpp"

using namespace testing;

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

/*TEST(TestConvexHull, TestVerticalPoints)
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
  EXPECT_TRUE(convexHull[0] == ProjectLibrary::Point(0, 1.7, numPoints++));
  EXPECT_TRUE(convexHull[1] == ProjectLibrary::Point(0, 6, numPoints++));
  EXPECT_TRUE(convexHull[2] == ProjectLibrary::Point(0, 5.2, numPoints++));
  EXPECT_TRUE(convexHull[3] == ProjectLibrary::Point(0, 5, numPoints++));
  EXPECT_TRUE(convexHull[4] == ProjectLibrary::Point(0, 4.3, numPoints++));
  EXPECT_TRUE(convexHull[5] == ProjectLibrary::Point(0, 3.1, numPoints++));
  EXPECT_TRUE(convexHull[6] == ProjectLibrary::Point(0, 3, numPoints++));
  EXPECT_TRUE(convexHull[7] == ProjectLibrary::Point(0, 2, numPoints++));

}*/


#endif //__TEST_EMPTY_H
