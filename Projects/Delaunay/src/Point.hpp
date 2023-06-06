#include <iostream>
#include "Eigen/Eigen"
#include <fstream>
#include <queue>

using namespace std;

namespace ProjectLibrary{

class Point
{
  private:

    ///Coordinate dei punti
    double x,y;

    ///Id. Per ora c'è ma a me sembra piuttosto superfluo
    int id;


  public:

    /// Ricavo x ed y del punto. Utile per accesso a dati privati per funzioni esterne
    double getX() const{return x;}
    double getY() const{return y;}
    int getID(){return id;}

    /// Costruttore
    Point(const double& x = 0.0, const double& y = 0.0, const int& id = 0);

    string Show() const
    {
        stringstream conc;
        conc << "x: " << x << ", y: " << y << endl;
        return conc.str();
    }

};

inline bool operator==(const Point& p1, const Point& p2)
{
    return ( p1.getX() == p2.getX() && p1.getY() == p2.getY());
}

inline bool operator!=(const Point& p1, const Point& p2)
{
    return !(p1==p2);
}

inline bool operator>(const Point& p1, const Point& p2)
{
    if (p1.getX()==p2.getX()){return p1.getY()>p2.getY();}
    else {return p1.getX()>p2.getX();}
}

inline bool operator<=(const Point& p1, const Point& p2)
{
    return !(p1>p2);
}

}
