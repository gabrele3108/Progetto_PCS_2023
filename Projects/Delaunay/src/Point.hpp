#include <iostream>
#include "Eigen/Eigen"
#include <fstream>
#include <queue>

using namespace std;

namespace ProjectLibrary{

constexpr double max_tolerance(const double& x, const double& y)
{
  return x > y ? x : y;
}


class Point
{
  private:

    ///Coordinate dei punti
    double x,y;

    ///Id. Per ora c'è ma a me sembra piuttosto superfluo
    int id;

    /// Gestione tolleranze

    static constexpr double geometricTol = 1.0e-12;
    static constexpr double geometricTol_Squared = max_tolerance(Point::geometricTol * Point::geometricTol,
                                                                 numeric_limits<double>::epsilon());


  public:

    Point* succ;
    Point* prec;

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
    friend bool ccwHull(const Point &p1, const Point &p2, const Point &p3);
    friend bool intersect(const Point& p1, const Point& p2, const Point& p3, const Point& p4);

};

inline double normSquared(const double& x, const double& y)
{
  return x * x + y * y;
}

inline bool operator==(const Point& p1, const Point& p2)
{
  return (normSquared(p1.x - p2.x, p1.y - p2.y) <=
          Point::geometricTol * Point::geometricTol *
          max(normSquared(p1.x, p1.y), normSquared(p2.x, p2.y)));
}

inline bool operator!=(const Point& p1, const Point& p2)
{
    return !(p1==p2);
}

inline bool operator>(const Point& p1, const Point& p2)
{
    if (abs(p1.x-p2.x)<Point::geometricTol){return p1.y > p2.y + Point::geometricTol * max(abs(p1.y),abs(p2.y));}
    else {return p1.x>p2.x + Point::geometricTol*max(abs(p1.x),abs(p2.x));}
}

inline bool operator<=(const Point& p1, const Point& p2)
{
    return !(p1>p2);
}

/// La funzione ccw ritorna "True" se p1, p2 e p3 sono ordinati in senso antiorario o collineari e "False" altrimenti
/// ccwHull ha specifiche diverse e serve per l'algoritmo di convexHull


bool ccw(const Point &p1, const Point &p2, const Point &p3);
bool ccwHull(const Point &p1, const Point &p2, const Point &p3);

/// La funzione intersect ritorna "True" se il segmento p1-p2 interseca il segmento p3-p4 e "False" altrimenti.

bool intersect(const Point& p1, const Point& p2, const Point& p3, const Point& p4);

/// Scriviamo la funzione Area (di un triangolo) nella libreria e non in una classe perchè in questo modo posso calcolare le aree
/// senza creare ogni volta degli oggetti triangolo

double Area(const Point &p1, const Point &p2, const Point &p3);

}
