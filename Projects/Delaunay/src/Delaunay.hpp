#ifndef __EMPTY_H
#define __EMPTY_H

#include <iostream>
#include "Eigen/Eigen"
#include <fstream>
#include <queue>
#include "convexHull.hpp"

using namespace std;


namespace ProjectLibrary
{

class Delaunay
  {
    private:
      unsigned int numPoints;

    public:
      std::vector<Triangle*> triangles;
      std::vector<Segment*> segments; //Utile per l'export
      std::vector<Point> points;
      std::vector<Point> triangulatedPoints;


      /// Queste funzioni sono modi più o meno efficienti di trovare il triangolo di area massima tra tutti i punti in points

      void maxAreaTriangle(); //Tested
      void maxAreaTriangleNSQ();

      /// Funzione "principale". Si occupa di generare la triangolazione di delauney a partire da un vettore di punti

      void triangulate();

      /// Questa funzione serve ad importare il set di punti su cui effettuare la triangolazione

      void importMesh(const string& path);

      /// Questa funzione prende in input due punti e se sono connessi mi ritorna il segmento che li connette

      int getSegmentIndex(Point& p1, Point& p2);

      /// Questa funzione controlla l'ipotesi di Delauney per il nuovo punto aggiunto

      void checkDelaunay(std::queue<Segment *> &queue);
      // Se il punto p che ho aggiunto è interno ad un certo triangolo t,
      // devo fare il check per gli al più tre triangoli adiacenti a t.
      // Se è necessario eseguire un flip,

      bool exportPoints(const string& outputFilePath);

      bool exportSegments(const string& path);

      /// Amicizie



};


}

#endif // __EMPTY_H
