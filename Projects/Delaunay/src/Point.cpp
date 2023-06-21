#include "Point.hpp"

namespace ProjectLibrary{

Point::Point(const double& x, const double& y, const int& id):
    x(x),
    y(y),
    id(id)
{
}

string Point::Show()
{
    stringstream conc;
    conc << "x: " << x << ", y: " << y <<", id: " << id << endl;
    return conc.str();
}

double Area(const Point& p1, const Point& p2, const Point& p3)
{return 0.5*(p1.x * p2.y + p2.x * p3.y + p3.x * p1.y - p2.x * p1.y - p3.x * p2.y - p1.x * p3.y);}

bool ccw(const Point&  p1, const Point& p2, const Point& p3){
    return ((p3.y-p1.y)*(p2.x-p1.x)>=(p2.y-p1.y)*((p3.x-p1.x)));
}

bool intersect(const Point &p1, const Point &p2, const Point &p3, const Point &p4)
{
    if (Area(p1,p2,p3) == 0 &&
            Area(p1,p2,p4) == 0 &&
            Area(p1,p3,p4) == 0 &&
            Area(p2,p3,p4) == 0)
    {
        /// Se entro qui, i 4 punti sono colineari. Ho molteplici casi

        Point ls1 = (p1>p2?p2:p1);
        Point rs1 = (p1>p2?p1:p2);
        Point ls2 = (p3>p4?p4:p3);
        Point rs2 = (p3>p4?p3:p4);
        if ((rs1>ls2 && ls1 <= ls2) || (ls2>rs1 && ls2 <= ls1)) {return true;}
        if ((rs1 <= ls2) || rs2 <= ls1) {return false;}

    }
    return (ccw(p1,p3,p4) != ccw(p2,p3,p4)) && (ccw(p1,p2,p3) != ccw(p1,p2,p4));
}

}
