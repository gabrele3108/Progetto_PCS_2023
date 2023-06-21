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

    /// Costruttore
    Point(const double& x = 0.0, const double& y = 0.0, const int& id = 0);

    string Show();

    /// Amicizie

    friend class Triangle;
    friend class Segment;
    friend class Delaunay;

    friend bool operator==(const Point& p1, const Point& p2);
    friend bool operator!=(const Point& p1, const Point& p2);
    friend bool operator>(const Point& p1, const Point& p2);
    friend bool operator<=(const Point& p1, const Point& p2);

    friend double Area(const Point &p1, const Point &p2, const Point &p3);
    friend bool ccw(const Point &p1, const Point &p2, const Point &p3);
    friend bool intersect(const Point& p1, const Point& p2, const Point& p3, const Point& p4);

};

inline bool operator==(const Point& p1, const Point& p2)
{
    return ( p1.x == p2.x && p1.y == p2.y);
}

inline bool operator!=(const Point& p1, const Point& p2)
{
    return !(p1==p2);
}

inline bool operator>(const Point& p1, const Point& p2)
{
    if (p1.x==p2.x){return p1.y>p2.y;}
    else {return p1.x>p2.x;}
}

inline bool operator<=(const Point& p1, const Point& p2)
{
    return !(p1>p2);
}

/// La funzione ccw ritorna "True" se p1, p2 e p3 sono ordinati in senso antiorario o collineari e "False" altrimenti

bool ccw(const Point &p1, const Point &p2, const Point &p3);

/// La funzione intersect ritorna "True" se il segmento p1-p2 interseca il segmento p3-p4 e "False" altrimenti.

bool intersect(const Point& p1, const Point& p2, const Point& p3, const Point& p4);

/// Scriviamo la funzione Area (di un triangolo) nella libreria e non in una classe perchè in questo modo posso calcolare le aree
/// senza creare ogni volta degli oggetti triangolo

double Area(const Point &p1, const Point &p2, const Point &p3);

}
