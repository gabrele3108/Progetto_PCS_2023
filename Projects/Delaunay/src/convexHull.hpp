#include "Point.hpp"

namespace ProjectLibrary{


void MergeHulls(vector<Point>& sortedV,
                const unsigned int& cx);


void MergeHull(vector<Point>& sortedV,
               const unsigned int& sx,
               const unsigned int& dx);




vector<Point> ConvexHull(vector<Point> points);

}
