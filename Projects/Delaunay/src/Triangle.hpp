#include "Segment.hpp"

using namespace std;

namespace ProjectLibrary{

class Triangle{
  private:
    Point p1, p2, p3;
  public:
    std::array<Segment*,3> segs;    

    /// Costruttori

    Triangle(const Point& pp1,const Point& pp2,const Point& pp3);
    Triangle();

    /// Queste funzioni servono per settare i tre segmenti. E' necessario definirle e non è possibile crearli
    /// direttamente nel costruttore perchè il costruttore dei triangoli non ha a disposizione la struttura della classe
    /// segmento. Le funzioni setS1, setS2 e setS3 sono comode in quanto più rapide di setSegment.
    // Snellire questa parte in futuro.

    void setS1(Segment *s){segs[0] = s;}
    void setS2(Segment *s){segs[1] = s;}
    void setS3(Segment *s){segs[2] = s;}
    void setSegment(Segment *s);

    /// La seguente funzione prende in input un segmento e restituisce il terzo punto.

    Point *ThirdPoint(Segment *s);

    /// La seguente funzione prende in input un segmento e restituisce gli altri due.

    void nonAdjSeg(const Segment* adjS, Segment *&s1,Segment *&s2);

    /// Le seguenti funzioni controllano se il punto p appartiene rispettivamente al cerchio circoscritto al triangolo o al triangolo stesso

    bool insideOfC(Point p);
    bool insideOfT(Point p);

    /// Funzione Show, utile per i test

    string Show();

    /// Amicizie

    friend class Delaunay;

    friend bool operator==(const Triangle& t1, const Triangle& t2);
    friend bool operator!=(const Triangle& t1, const Triangle& t2);

};

inline bool operator==(const Triangle& t1, const Triangle& t2)
    {
        return ((t1.p1 == t2.p1 &&
                t1.p2 == t2.p2 &&
                t1.p3 == t2.p3));
    }

inline bool operator!=(const Triangle& t1, const Triangle& t2)
    {return !(t1==t2);}

}
