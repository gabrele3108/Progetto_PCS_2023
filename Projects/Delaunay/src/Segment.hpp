#include "Point.hpp"

using namespace std;

namespace ProjectLibrary{

class Triangle;

class Segment
{
  private:
    Point p1,p2;
    Triangle* adj1;
    Triangle* adj2;
    unsigned int c = 0;
  public:
    Segment(const Point&  pp1, const Point& pp2):
        p1(pp1),
        p2(pp2)
    {
        if (p1<=p2){
            p1 = pp2;
            p2 = pp1;
        }
    }

    const Point& getP1() const {return p1;}
    const Point& getP2() const{return p2;}

    /// I seguenti metodi restituiscono puntatori ai triangoli adiacenti al segmento, se questi sono stati definiti.
    /// Darò per scontato che siano dati defini: il check avverrà esternamente.

    Triangle *getAdj1(){return adj1;}
    Triangle *getAdj2(){return adj2;}

    /// Il seguente metodo connette ad un segmento un triangolo ed aggiorna il contatore di adiacenze c;

    void connectTriangle(Triangle *t1);

    /// Il seguente metodo disconnette un triangolo dal segmento.
    /// Utile quando devo effettuare un flip oppure quando devo suddividere un triangolo in tre parti

    void disconnectTriangle(Triangle *t1);

    /// Il seguente metodo mi dice di quanti triangoli è parte il mio segmento

    unsigned int getC(){return c;}

    string Show() const
    {
        stringstream conc;
        conc << "P1: " << p1.Show() << "P2: " << p2.Show() << "Il segmento connette " << c << " triangoli" << endl;
        return conc.str();
    }

};

inline bool operator==(const Segment s1, const Segment s2)
{
    return (s1.getP1()==s2.getP1() && (s1.getP2() == s2.getP2()));
}

inline bool operator!=(const Segment s1, const Segment s2)
{
    return !(s1==s2);
}

}
