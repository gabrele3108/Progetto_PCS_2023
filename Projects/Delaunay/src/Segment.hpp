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

    /// Il seguente metodo connette ad un segmento un triangolo ed aggiorna il contatore di adiacenze c;

    void connectTriangle(Triangle *t1);

    /// Il seguente metodo disconnette un triangolo dal segmento.
    /// Utile quando devo effettuare un flip oppure quando devo suddividere un triangolo in tre parti

    void disconnectTriangle(Triangle *t1);


    string Show()
    {
        stringstream conc;
        conc << "p1: " << p1.Show() << "p2: " << p2.Show() << "Il segmento è adiacente a" << c << " triangoli" << endl;
        return conc.str();
    }

    /// Amicizie

    friend Triangle;
    friend class Delaunay;

    friend bool operator==(const Segment s1, const Segment s2);
    friend bool operator!=(const Segment s1, const Segment s2);

};

inline bool operator==(const Segment s1, const Segment s2)
{
    return ((s1.p1==s2.p1) && (s1.p2 == s2.p2));
}

inline bool operator!=(const Segment s1, const Segment s2)
{
    return !(s1==s2);
}

}
