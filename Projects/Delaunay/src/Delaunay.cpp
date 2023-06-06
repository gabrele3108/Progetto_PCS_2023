#include "Delaunay.hpp"
#include "Eigen/Eigen"

using namespace Eigen;
namespace ProjectLibrary
{

// Brute force. Riscrivi usando
// https://stackoverflow.com/questions/1621364/how-to-find-largest-triangle-in-convex-hull-aside-from-brute-force-search/44335834#44335834
void Delaunay::maxAreaTriangle(){
    unsigned int pSize = points.size();
    double maxArea = 0;
    array<unsigned int,3> bestIds;
    for (unsigned int i = 2; i < pSize; i++){
        for (unsigned int j = 1; j < i; j++){
            for (unsigned int k = 0; k < j; k++){
                double currentArea = abs(Area(points[i],points[j], points[k]));
                if (currentArea>maxArea){
                    maxArea = currentArea;
                    bestIds[0] = k;
                    bestIds[1] = j;
                    bestIds[2] = i;
                }
            }
        }
    }

    /// Costruzione dell'oggetto triangolo e degli oggetti segmento

    Triangle *maxT = new Triangle(points[bestIds[0]],points[bestIds[1]],points[bestIds[2]]);
    Segment *s1 = new Segment(maxT->p1,maxT->p2);
    Segment *s2 = new Segment(maxT->p2,maxT->p3);
    Segment *s3 = new Segment(maxT->p3,maxT->p1);

    maxT->setS1(s1);maxT->setS2(s2);maxT->setS3(s3);
    s1->connectTriangle(maxT);s2->connectTriangle(maxT);s3->connectTriangle(maxT);

    /// Aggiornamento della mesh

    segments.push_back(s1);segments.push_back(s2);segments.push_back(s3);

    triangles.push_back(maxT);

    triangulatedPoints.push_back(maxT->p1);
    triangulatedPoints.push_back(maxT->p2);
    triangulatedPoints.push_back(maxT->p3);

    points.erase(points.begin() + bestIds[0]);
    points.erase(points.begin() + bestIds[1]-1);
    points.erase(points.begin() + bestIds[2]-2);

}

void Delaunay::importMesh(const string& path){
    ifstream file;

    file.open(path);


    //if(file.fail())
    //   return false; Eventualmente cambiamo il void in bool.

    list<string> listLines;
    string line;


    while (getline(file, line))
    {
      listLines.push_back(line);
    }
    listLines.pop_front();


    // Controllo se effettivamente ho ricevuto punti
    //int numPoints = listLines.size();

    //if (numPoints == 0)
    //{
    //  cerr << "There is no cell 2D" << endl;
    //  return false;
    //}


    for (const string& line : listLines)
    {
      istringstream converter(line);

      unsigned int id;
      double x;
      double y;

      converter >> id;
      converter >> x;
      converter >> y;

      Point* p = new Point(x,y,id);

      Delaunay::points.push_back(*p);

    }
    file.close();
    //return true;
}

bool Delaunay::exportPoints(const string& outputFilePath){
          ofstream file;

          file.open(outputFilePath);
          if (file.fail())
          {
            std::cerr<< "file opening failed"<< std::endl;
            return false;
          }
          file<<"id;x;y"<<endl;
          std::stringstream converterID;
          std::stringstream converterX;
          std::stringstream converterY;
          for(unsigned int i=0;i<triangulatedPoints.size();i++){

              converterID.str("");
              converterX.str("");
              converterY.str(""); //non so se sia necessario, sembra funzionare anche senza.
              converterID<<triangulatedPoints[i].id;
              converterX<<triangulatedPoints[i].x;
              converterY<<triangulatedPoints[i].y;
              file<<converterID.str()<<";"<<converterX.str()<<";"<<converterY.str()<<endl;
          }

          file.close();
          return true;
      }

      bool Delaunay::exportSegments(const string& path)
      {
          ofstream file;
          file.open(path);
          if(file.fail()){
              std::cerr<<"file opening failed"<<std::endl;
              return false;
          }
          file<<"x1;y1;x2;y2"<<std::endl;
          std::stringstream converterX1;
          std::stringstream converterY1;
          std::stringstream converterX2;
          std::stringstream converterY2;
          std::stringstream converterC;
          for(Segment* s:segments){
              converterX1.str("");
              converterX2.str("");
              converterY1.str("");
              converterY2.str("");
              converterC.str("");
              converterX1<<s->p1.x;
              converterY1<<s->p1.y;
              converterX2<<s->p2.x;
              converterY2<<s->p2.y;
              converterC<<s->c;
              file<<converterX1.str()<<";"<<converterY1.str()<<";"<<converterX2.str()<<";"<<converterY2.str()<<";"<<converterC.str()<<endl;
          }
          file.close();
          return true;
    }







int Delaunay::getSegmentIndex(Point& p1, Point& p2)
{
    Segment tmpS = Segment(p1,p2);
    unsigned int f = 0;
    bool found = 0;
    while (f < segments.size() && !found)
    {
        if (*segments[f]==tmpS)
        {
            found = true;
        }
        else{f++;}
    }
    return f;

}

void Delaunay::triangulate(){
    unsigned int numPoints = points.size();
    if (numPoints > 3){

        /// Creazione del triangolo di area massima.

        maxAreaTriangle();

        /// Salvo i punti "sul bordo" della triangolazione nel vettore extP.
        /// Questo vettore conterrà il convex hull dei punti aggiunti alla triangolazione


        std::vector<Point> extP = triangulatedPoints;

        /// Aggiunta di un nuovo punto alla triangolazione

        for (unsigned i = 0; i < numPoints-3; i++){
            /// queue conterrà i segmenti su cui controllare i flip. Il check dei flip finirà quando queue tornerà vuota

            std::queue<Segment*> queue;

            /// Per ogni triangolo controllo se currentP è al suo interno. Mi fermo se trovo
            /// un triangolo che lo contiene

            bool check = true;
            bool onSegment = false;
            bool onExtSeg = false;
            unsigned int j = 0;
            unsigned int numTriangles = triangles.size();
            Segment* currentS = nullptr;
            while (j < numTriangles && check && !onSegment){
                if (triangles[j]->insideOfT(points[i]))
                {
                    unsigned int sC = 0;
                    check = false;
                    while (sC<3 && !onSegment)
                    {
                        if (Area(triangles[j]->segs[sC]->p1,triangles[j]->segs[sC]->p2,points[i]) == 0)
                        {onSegment = true;}
                        else{sC++;};
                    }
                    if (onSegment)
                    {

                        currentS = triangles[j]->segs[sC];
                        if (currentS->c == 1)
                        {onExtSeg = true;}
                    }
                }
                else{j++;}
            }

            /// Dopo questo while, se check è ancora true, il punto è fuori dalla triangolazione
            /// altrimenti, è interno ad un triangolo.

            if (!check && !onSegment)
            {
                cout << "il punto" << i << "dovrebbe essere dentro un triangolo ma non su un segmento" << endl;

                /// In questo caso la prima cosa da fare è costruire i tre nuovi triangoli.
                /// Inizio creando i segmenti ed i triangoli che non esistono ancora:


                Segment *newS1 = new Segment(points[i],triangles[j]->p1); // Connette p1 e p
                Segment *newS2 = new Segment(points[i],triangles[j]->p2); // Connette p2 e p
                Segment *newS3 = new Segment(points[i],triangles[j]->p3); // Connette p3 e p


                Triangle *newT1 = new Triangle(triangles[j]->p1,triangles[j]->p2,points[i]); // p1, p2, p
                Triangle *newT2 = new Triangle(triangles[j]->p2,triangles[j]->p3,points[i]); // p2, p3, p
                Triangle *newT3 = new Triangle(triangles[j]->p3,triangles[j]->p1,points[i]); // p3, p1, p

                /// Recupero i segmenti "esterni" ed elimino il triangolo da essi.
                /// Questa cosa potrei farla in un distruttore nella classe triangolo


                Segment *s1 = triangles[j]->segs[0]; // Connette p1 e p2
                Segment *s2 = triangles[j]->segs[1]; // Connette p2 e p3
                Segment *s3 = triangles[j]->segs[2]; // Connette p3 e p1

                s1->disconnectTriangle(triangles[j]);
                s2->disconnectTriangle(triangles[j]);
                s3->disconnectTriangle(triangles[j]);

                /// Sistemo i segmenti nei triangoli a cui appartengono

                newT1->setSegment(s1);
                newT1->setSegment(newS1);
                newT1->setSegment(newS2);

                newT2->setSegment(s2);
                newT2->setSegment(newS2);
                newT2->setSegment(newS3);

                newT3->setSegment(s3);
                newT3->setSegment(newS3);
                newT3->setSegment(newS1);

                s1->connectTriangle(newT1);
                s2->connectTriangle(newT2);
                s3->connectTriangle(newT3);

                newS1->connectTriangle(newT1);
                newS1->connectTriangle(newT3);

                newS2->connectTriangle(newT2);
                newS2->connectTriangle(newT1);

                newS3->connectTriangle(newT3);
                newS3->connectTriangle(newT2);

                /// Aggiungo i segmenti alla lista di segmenti

                segments.push_back(newS1);segments.push_back(newS2);segments.push_back(newS3);

                /// Aggiungo i tre nuovi triangoli alla mesh

                triangles.push_back(newT1);
                triangles.push_back(newT2);
                triangles.push_back(newT3);

                /// La seconda cosa da fare è salvare i segmenti che andranno controllati in Delaunay

                if (triangles[j]->segs[0]->c==2){queue.push(triangles[j]->segs[0]);}
                if (triangles[j]->segs[1]->c==2){queue.push(triangles[j]->segs[1]);}
                if (triangles[j]->segs[2]->c==2){queue.push(triangles[j]->segs[2]);}

                /// L'ultima cosa da fare è eliminare il triangolo che contiene il punto
                /// dalla triangolazione

                triangles.erase(triangles.begin()+j);
            }

            if (!check && onSegment)
            {
                cout << "il punto " << i << "è su un segmento" << endl;
                if (onExtSeg)
                {
                    cout << "il punto " << i << "è su un segmento esterno" << endl;
                    /// Il triangolo che contiene il punto è triangles[j]
                    /// Il segmento che contiene il punto è currentS

                    /// Devo unire il punto a tutti gli altri tre punti del triangolo

                    /// Devo creare i tre nuovi segmenti
                    /// Devo creare due nuovi triangoli

                    /// Devo aggiungere il nuovo punto ad extP tra i punti che definiscono currentS

                    /// Devo eliminare il segmento currentS
                    /// Devo eliminare il triangolo triangles[j]

                    /// Eseguo la fase di "distruzione" ed in extP inserisco il terzo punto del triangolo
                    /// Poi lascio che l'if successivo faccia il resto

                    /// Per costruzione so che i punti del segmento currentS sono punti esterni consecutivi
                    /// quindi saranno individuabili con "extP[k]" ed "extP[k+1]" (o comunque extP[end] ed extP[0])
                    /// Ma non so quale dei due viene prima, ne in che posizione siano, quindi prima di tutto devo localizzarli

                    /// La seguente funzione trova manualmente l'indice in extP del primo punto di currentS

                    unsigned int firstInd = 0;

                    bool found = false;

                    if ((extP[extP.size()-1] == currentS->p1 || extP[extP.size()-1] == currentS ->p2) &&
                         (extP[0] == currentS->p1||extP[0] == currentS->p2))
                    {
                        firstInd = extP.size()-1;
                        found = true;
                    }
                    while (!found)
                    {
                        if (extP[firstInd] == currentS->p1 || extP[firstInd] == currentS->p2)
                        {
                            found = true;
                        }
                        else {firstInd++;}
                    }
                    if (firstInd != extP.size()-1)
                    {
                        extP.insert(extP.begin()+firstInd+1,*triangles[j]->ThirdPoint(currentS));
                    }
                    else {extP.push_back(*triangles[j]->ThirdPoint(currentS));}


                    Segment* oldS1;
                    Segment* oldS2;

                    triangles[j]->nonAdjSeg(currentS,oldS1,oldS2);
                    oldS1->disconnectTriangle(triangles[j]);
                    oldS2->disconnectTriangle(triangles[j]);

                    currentS->disconnectTriangle(triangles[j]);

                    segments.erase(std::find(segments.begin(),segments.end(),currentS));
                    triangles.erase(triangles.begin()+j);
                    check = true;
                    onSegment = false;
                }

                else
                {
                    /// Il segmento che contiene il punto è *currentS. Seleziono i due triangoli che contengono il punto

                    Triangle *t1 = currentS->adj1;
                    Triangle *t2 = currentS->adj2;

                    /// Questi due triangoli andranno distrutti, ma prima devo creare 4 nuovi segmenti: devono unire points[i]
                    /// agli estremi di currentS e ai due punti di t1 e t2 non uniti da currentS.

                    /// Recupero i 4 punti del quadrilatero

                    Point *tp1 = t1->ThirdPoint(currentS);
                    Point *tp2 = t2->ThirdPoint(currentS);
                    Point sp1 = currentS->p1;
                    Point sp2 = currentS->p2;

                    /// Recupero i 4 segmenti del quadrilatero

                    Segment* t1S1 = nullptr;
                    Segment* t1S2 = nullptr;
                    Segment* t2S1 = nullptr;
                    Segment* t2S2 = nullptr;

                    t1->nonAdjSeg(currentS,t1S1,t1S2);
                    t2->nonAdjSeg(currentS,t2S1,t2S2);

                    /// Disconnetto i triangoli da currentS (Potenzialmente inutile tanto currentS devo eliminarlo) e
                    /// dai 4 segmenti del quadrilatero

                    currentS->disconnectTriangle(t1);
                    currentS->disconnectTriangle(t2);

                    t1S1->disconnectTriangle(t1);
                    t1S2->disconnectTriangle(t1);

                    t2S1->disconnectTriangle(t2);
                    t2S2->disconnectTriangle(t2);

                    /// Unisco il punto nuovo ai 4 punti del quadrilatero

                    Segment* newS1 = new Segment(points[i],*tp1);
                    Segment* newS2 = new Segment(sp2,points[i]);
                    Segment* newS3 = new Segment(sp1,points[i]);
                    Segment* newS4 = new Segment(points[i],*tp2);

                    /// Creo i 4 nuovi triangoli e li collego ai rispettivi segmenti

                    Triangle* newT1 = new Triangle(sp1,points[i],*tp1);
                    Triangle* newT2 = new Triangle(sp2,points[i],*tp1);
                    Triangle* newT3 = new Triangle(sp1,points[i],*tp2);
                    Triangle* newT4 = new Triangle(sp2,points[i],*tp2);

                    newT1->setSegment(newS1);
                    newT1->setSegment(newS3);

                    newT2->setSegment(newS2);
                    newT2->setSegment(newS1);

                    newT3->setSegment(newS3);
                    newT3->setSegment(newS4);

                    newT4->setSegment(newS4);
                    newT4->setSegment(newS2);

                    if ((t1S1->p1 == sp1 || t1S1->p2 == sp1))
                    {
                        newT1->setSegment(t1S1);
                        newT2->setSegment(t1S2);
                        t1S1->connectTriangle(newT1);
                        t1S2->connectTriangle(newT2);
                    }
                    else
                    {
                        newT1->setSegment(t1S2);
                        newT2->setSegment(t1S1);
                        t1S1->connectTriangle(newT2);
                        t1S2->connectTriangle(newT1);
                    }



                    if ((t2S1->p1 == sp1 || t2S1->p2 == sp1))
                    {
                        newT3->setSegment(t2S1);
                        newT4->setSegment(t2S2);
                        t2S1->connectTriangle(newT3);
                        t2S2->connectTriangle(newT4);
                    }
                    else
                    {
                        newT3->setSegment(t2S2);
                        newT4->setSegment(t2S1);
                        t2S1->connectTriangle(newT4);
                        t2S2->connectTriangle(newT3);
                    }

                    newS1->connectTriangle(newT1);
                    newS1->connectTriangle(newT2);

                    newS2->connectTriangle(newT2);
                    newS2->connectTriangle(newT4);

                    newS3->connectTriangle(newT1);
                    newS3->connectTriangle(newT3);

                    newS4->connectTriangle(newT4);
                    newS4->connectTriangle(newT3);

                    segments.erase(std::find(segments.begin(),segments.end(),currentS));
                    triangles.erase(std::find(triangles.begin(),triangles.end(),t1));
                    triangles.erase(std::find(triangles.begin(),triangles.end(),t2));

                    segments.push_back(newS1);segments.push_back(newS2);segments.push_back(newS3);segments.push_back(newS4);
                    triangles.push_back(newT1);triangles.push_back(newT2);triangles.push_back(newT3);triangles.push_back(newT4);

                    if (t1S1->c== 2){queue.push(t1S1);}
                    if (t1S2->c== 2){queue.push(t1S2);}
                    if (t2S1->c== 2){queue.push(t2S1);}
                    if (t2S2->c== 2){queue.push(t2S2);}

                }

            }

            if (check && !onSegment)
            {

                cout << "il punto " << i << "è all'esterno e non su un segmento" << endl;

                /// In questo altro caso bisogna unire il punto ad ogni altro punto della triangolazione
                /// trascurando però triangoli che si andrebbero a formare intersecando altri triangoli.

                //  /// Inizio ordinando i punti da sinistra verso destra (e dal basso verso l'alto, in caso di uguaglianza.
                //  /// Questa struttura è molto comoda quando devo stabilire quali punti restano esterni e quali diventano interni.

                // SortLibrary::MergeSort(extP,0,extP.size());

                ///In questo vettore salverò gli indici (in extP) dei punti esterni a cui devo connettere il punto appena aggiunto

                std::vector<int> toConnectIndex;

                /// Questo vettore conterrà tutti i segmenti che vado a creare unendo il punto

                std::vector<Segment*> newSegs;

                /// Itero per tutti i punti esterni per controllare a quali devo connettermi

                for (unsigned int j1 = 0; j1 < extP.size(); j1++){
                    bool checkConnect = true;

                    ///Seleziono ogni coppia di punti esterni (diversi dal primo).

                    unsigned int j2 = (j1 + 1)%extP.size();
                    while ((j2 != j1) && checkConnect){
                        if (intersect(points[i],extP[j1],extP[j2],extP[(j2+1)%extP.size()]))
                        {
                            j2 = j1;
                            checkConnect = false;
                        }
                        ++j2;
                        j2 = j2%extP.size();
                    }

                    /// Se non ho trovato intersezioni connetto il punto appena aggiunto al punto che sto considerando e salvo l'indice

                    if (checkConnect){
                        toConnectIndex.push_back(j1);
                        Segment *newS = new Segment(extP[j1],points[i]);
                        newSegs.push_back(newS);
                        segments.push_back(newS);
                    }
                }

                /// extP è il convexHull della triangolazione, oltre a tener conto di quali punti sono esterni,
                /// dunque una volta connesso ad un punto, sarò connesso ad un certo numero di punti successivi ad esso.
                /// Salvo l'indice che il primo e l'ultimo hanno in extP.

                unsigned int firstConnect = toConnectIndex[0];
                unsigned int lastConnect = toConnectIndex[toConnectIndex.size()-1];

                unsigned int tfc = 0;
                bool found = 0;
                while (tfc < toConnectIndex.size()-1 && !found)
                {
                    if (toConnectIndex[tfc+1] != toConnectIndex[tfc] + 1)
                    {
                        firstConnect = toConnectIndex[tfc+1];
                        lastConnect = toConnectIndex[tfc];
                        found = true;
                    }
                    tfc++;
                }
                if (!found){tfc = 0;}

                for (unsigned int tci = 0; tci < toConnectIndex.size()-1;tci++){

                    Triangle *newT = new Triangle(points[i],extP[(firstConnect+tci)%extP.size()],extP[(firstConnect+tci+1)%extP.size()]);
                    int m = getSegmentIndex(extP[(firstConnect+tci)%extP.size()],extP[(firstConnect+tci+1)%extP.size()]);

                    newT->setSegment(segments[m]);
                    newT->setSegment(newSegs[(tfc + tci)%newSegs.size()]);
                    newT->setSegment(newSegs[(tfc + tci + 1)%newSegs.size()]);

                    segments[m]->connectTriangle(newT);
                    newSegs[(tfc + tci)%newSegs.size()]->connectTriangle(newT);
                    newSegs[(tfc + tci + 1)%newSegs.size()]->connectTriangle(newT);


                    queue.push(segments[m]);
                    triangles.push_back(newT);


                }


                /// I punti compresi tra questi due non sono più esterni, dunque è necessario rimuoverli da extP. C'è da tenere conto
                /// del caso in cui firstConnect è maggiore di lastConnect.

                if (lastConnect<firstConnect)
                {
                    unsigned int toDelRight = extP.size()-firstConnect-1;
                    for (unsigned int k = 0; k<toDelRight;k++){extP.pop_back();}
                    for (unsigned int k = 0; k<lastConnect;k++)
                    {
                        extP.erase(extP.begin());
                    }
                    extP.push_back(points[i]);
                }
                else
                {
                    unsigned int toDelMid = lastConnect-firstConnect-1;
                    for (unsigned int k = 0; k<toDelMid;k++)
                    {
                        extP.erase(extP.begin()+firstConnect+1);
                    }
                    extP.insert(extP.begin()+firstConnect + 1,points[i]);
                }
            }




            /// A questo punto è necessario verificare l'ipotesi di Delauney. Lo faccio a partire dalla coda queue
            triangulatedPoints.push_back(points[i]);
            checkDelaunay(queue);
            exportPoints("C:/Users/aless/Desktop/PCS/PCS2023_Exercises/Projects/Delaunay/Dataset/ProvaPoints.csv");
            exportSegments("C:/Users/aless/Desktop/PCS/PCS2023_Exercises/Projects/Delaunay/Dataset/ProvaSegs.csv");
        }
    }

}


//Queue dev'essere inizializzata con i segmenti appartenenti al triangolo contenente il punto inizialmente
//oppure ai segmenti esterni a cui questo viene unito. Quindi queue deve contenere esattamente questi segmenti.
//Dopo un flip devo controllare tutti i segmenti del quadrilatero che si va a creare e che sono adiacenti ad un altro triangolo
void Delaunay::checkDelaunay(std::queue<Segment*>& queue){
    unsigned int numFlip = 0;
    while (!queue.empty())
    {
        Segment *currentS = queue.front();
        Triangle *currentAdj1 = currentS->adj1;
        Triangle *currentAdj2 = currentS->adj2;
        Point *tP2 = currentAdj2->ThirdPoint(currentS);
        if (currentAdj1->insideOfC(*tP2))
        {
            cout << ++numFlip << endl;
            //Esegui flip
            /// Come prima cosa recupero il terzo punto del primo triangolo di adiacenza.
            /// Inoltre recupero i 4 segmenti che definiscono il quadrilatero su cui effettuo il flip
            /// Dovrò creare un nuovo segmento che unisce tp1 e tp2.

            Point *tP1 = currentAdj1->ThirdPoint(currentS);
            Segment *newT1S1;
            Segment *newT1S2;
            Segment *newT2S1;
            Segment *newT2S2;
            Segment *newS = new Segment(*tP1, *tP2);
            currentAdj1->nonAdjSeg(currentS,newT1S1,newT1S2); // Contengono tutti tP1
            currentAdj2->nonAdjSeg(currentS,newT2S1,newT2S2); // Contengono tutti tP2

            /// Sconnetto i triangoli da eliminare dai segmenti

            newT1S1->disconnectTriangle(currentAdj1);
            newT1S2->disconnectTriangle(currentAdj1);
            newT2S1->disconnectTriangle(currentAdj2);
            newT2S2->disconnectTriangle(currentAdj2);


            /// Creo i due nuovi triangoli che andranno a rimpiazzare quelli attualmente adiacenti a currentS

            Triangle *newT1 = new Triangle(currentS->p1,*tP2,*tP1);
            Triangle *newT2 = new Triangle(currentS->p2,*tP1,*tP2);

            /// Aggiungo ai nuovi triangoli i loro segmenti e viceversa

            newT1->setSegment(newS);
            newT2->setSegment(newS);


            if (currentS->p1 == newT1S1->p1 || currentS->p1 == newT1S1->p2)
            {
                newT1->setSegment(newT1S1);
                newT1S1->connectTriangle(newT1);
                newT2->setSegment(newT1S2);
                newT1S2->connectTriangle(newT2);
            }
            else
            {
                newT1->setSegment(newT1S2);
                newT1S2->connectTriangle(newT1);
                newT2->setSegment(newT1S1);
                newT1S1->connectTriangle(newT2);
            }

            if (currentS->p1 == newT2S1->p1 || currentS->p1 == newT2S1->p2)
            {
                newT1->setSegment(newT2S1);
                newT2S1->connectTriangle(newT1);
                newT2->setSegment(newT2S2);
                newT2S2->connectTriangle(newT2);
            }
            else
            {
                newT1->setSegment(newT2S2);
                newT2S2->connectTriangle(newT1);
                newT2->setSegment(newT2S1);
                newT2S1->connectTriangle(newT2);
            }

            newS->connectTriangle(newT1);
            newS->connectTriangle(newT2);

            /// Aggiungo alla coda da controllare per i flip i 4 segmenti appena recuperati,
            /// se questi sono connessi a più di un triangolo

            if (newT1S1->c==2){queue.push(newT1S1);}
            if (newT1S2->c==2){queue.push(newT1S2);}
            if (newT2S1->c==2){queue.push(newT2S1);}
            if (newT2S2->c==2){queue.push(newT2S2);}

            /// Devo rimuovere dai segmenti il segmento currentS e da triangles i triangoli adiacenti

            segments.erase(std::find(segments.begin(),segments.end(),currentS));
            triangles.erase(std::find(triangles.begin(),triangles.end(),currentAdj1));
            triangles.erase(std::find(triangles.begin(),triangles.end(),currentAdj2));

            /// Infine aggiungo i nuovi triangoli ed il nuovo segmento

            segments.push_back(newS);
            triangles.push_back(newT1);
            triangles.push_back(newT2);

        }
        queue.pop();
    }
}

}
