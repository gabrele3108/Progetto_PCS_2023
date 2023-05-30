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

    /// Queste funzioni restituiscono i tre punti che compongono il triangolo a partire da quello più a sinistra

    const Point& getP1() const {return p1;}
    const Point& getP2() const {return p2;}
    const Point& getP3() const {return p3;}

    /// Queste funzioni restituiscono i tre segmenti che compongono il triangolo a partire dal segmento che unisce P1 e P2

    Segment *getS1() {return segs[0];}
    Segment *getS2() {return segs[1];}
    Segment *getS3() {return segs[2];}

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

    /// La funzione ccw controlla se p1, p2 e p3 sono ordinati in senso antiorario

    bool ccw(Point p1, Point p2, Point p3){
    return ((p3.getY()-p1.getY())*(p2.getX()-p1.getX())>=(p2.getY()-p1.getY())*((p3.getX()-p1.getX())));
    }

    /// Le seguenti funzioni controllano se il punto p appartiene rispettivamente al cerchio circoscritto al triangolo o al triangolo stesso
    bool insideOfC(Point p);
    bool insideOfT(Point p);
    double Area();
};

inline bool operator==(const Triangle& t1, const Triangle& t2)
    {
        return ((t1.getP1() == t2.getP1() &&
                t1.getP2() == t2.getP2() &&
                t1.getP3() == t2.getP3()));
    };

}
