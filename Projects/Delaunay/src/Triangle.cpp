#include "Triangle.hpp"
#include "sorting.hpp"

using namespace Eigen;

namespace ProjectLibrary{

Triangle::Triangle(const Point& pp1, const Point& pp2,const Point& pp3)
{
    std::vector<Point> temp {pp1,pp2,pp3};
    SortLibrary::MergeSort(temp,0,2);
    p1 = temp[0];
    p2 = temp[1];
    p3 = temp[2];
    if(!ccw(p1,p2,p3))
    {
      p2 = temp[2];
      p3 = temp[1];
    }
}

bool Triangle::insideOfC(Point p)
{
    Point tmp1 = this->p1;
    Point tmp2 = this->p2;
    Point tmp3 = this->p3;
    // Introducendo queste variabili si risparmiano 6 calcoli!
    double adx = tmp1.x-p.x;
    double ady = tmp1.y-p.y;
    double bdx = tmp2.x-p.x;
    double bdy = tmp2.y-p.y;
    double cdx = tmp3.x-p.x;
    double cdy = tmp3.y-p.y;
    Matrix3d check {
        {adx,ady,(pow(adx,2)+pow(ady,2))},
        {bdx,bdy,(pow(bdx,2)+pow(bdy,2))},
        {cdx,cdy,(pow(cdx,2)+pow(cdy,2))}
    };
    return (check.determinant()>0);
}

bool Triangle::insideOfT(Point p)
{
    return (ccw(p1,p2,p) && ccw(p2,p3,p) && ccw(p3,p1,p));
}

Triangle::Triangle():
    p1(Point()),
    p2(Point()),
    p3(Point())
{}

void Triangle::setSegment(Segment *s)
{
    std::vector<Point> tmp =std::vector<Point>({s->p2,s->p1});
    bool hasP1 = (std::find(tmp.begin(),tmp.end(), p1) != tmp.end());
    bool hasP2 = (std::find(tmp.begin(),tmp.end(), p2) != tmp.end());
    bool hasP3 = (std::find(tmp.begin(),tmp.end(), p3) != tmp.end());
    if (hasP1 && hasP2){segs[0] = s;}
    if (hasP2 && hasP3){segs[1] = s;}
    if (hasP3 && hasP1){segs[2] = s;}
}

Point *Triangle::ThirdPoint(Segment *s)
{
    if (s == segs[0]) {return &p3;}
    if (s == segs[1]) {return &p1;}
    return &p2;
}

void Triangle::nonAdjSeg(const Segment* adjS, Segment *&ss1,Segment *&ss2)
{
    if (adjS == segs[0])
    {ss1 = segs[1]; ss2 = segs[2];}
    if (adjS == segs[1])
    {ss1 = segs[2]; ss2 = segs[0];}
    if (adjS == segs[2])
    {ss1 = segs[0]; ss2 = segs[1];}
}

string Triangle::Show()
{
    stringstream converter;
    converter << "This triangle is made of the following 3 points:\n" << "p1: " << p1.Show() << "\n" << "p2: " << p2.Show()<< "\n" << "p3: " << p3.Show() << endl;
    return converter.str();
}

}
