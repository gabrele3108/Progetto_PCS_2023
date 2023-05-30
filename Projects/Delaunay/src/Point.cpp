#include "Point.hpp"

namespace ProjectLibrary{

Point::Point(const double& x, const double& y, const int& id):
    x(x),
    y(y),
    id(id)
{
}

void Point::connect(Point& p)
{
    partOfSegment.push_back(p);
}

bool Point::isConnected(Point& p)
{
    std::vector<Point> tmp = this->partOfSegment;
    if(std::find(tmp.begin(),tmp.end(), p) != tmp.end()) {
        return true;
    }
    return false;
}

}
