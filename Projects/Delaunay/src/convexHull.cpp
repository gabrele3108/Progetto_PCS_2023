#include "sorting.hpp"
#include "convexHull.hpp"

namespace ProjectLibrary{


void MergeHulls(vector<Point>& sortedV,
                const unsigned int& cx)
{
    Point* uppLeft = &sortedV[cx];
    Point* uppRight = &sortedV[cx+1];
    bool checkUBridge = true;
    bool inconclusive1 = false;
    while (checkUBridge && !inconclusive1)
    {
        if (ccwHull(*uppLeft,*uppRight,*uppLeft->succ))
        {uppLeft = uppLeft->succ;}
        else if (ccwHull(*uppLeft,*uppRight,*uppRight->prec))
        {uppRight = uppRight->prec;}
        else
        {
            checkUBridge = false;
        }
    }


    Point* lowLeft = &sortedV[cx];
    Point* lowRight = &sortedV[cx+1];
    bool checkLBridge = true;
    bool inconclusive2 = false;

    while (checkLBridge && !inconclusive2)
    {
        if (!ccwHull(*lowLeft,*lowRight,*lowLeft->prec))
        {lowLeft = lowLeft->prec;}
        else if (!ccwHull(*lowLeft,*lowRight,*lowRight->succ))
        {lowRight = lowRight->succ;}
        else
        {
            checkLBridge = false;
        }
        /*if (*lowLeft == sortedV[cx] && *lowRight == sortedV[cx+1] && checkLBridge)
        {
            inconclusive2 = true;
            *lowLeft = sortedV[cx];
            *lowRight = sortedV[cx+1];
        }*/
    }

    if (inconclusive1 && inconclusive2)
    {
        uppLeft = uppLeft->succ;
        uppRight = uppRight->prec;
    }


    uppLeft->prec=uppRight;
    uppRight->succ=uppLeft;

    lowLeft->succ = lowRight;
    lowRight->prec = lowLeft;
}


void MergeHull(vector<Point>& sortedV,
               const unsigned int& sx,
               const unsigned int& dx)
{
  if (sx + 2 < dx){
      unsigned int cx = (sx + dx)/2;
      MergeHull(sortedV,sx,cx);
      MergeHull(sortedV,cx+1,dx);
      MergeHulls(sortedV,cx);
  }
  if(sx + 2 == dx){
      if (ccw(sortedV[sx],sortedV[sx+1],sortedV[sx+2])){
          sortedV[sx].succ = &sortedV[sx+1];
          sortedV[sx+1].succ = &sortedV[sx+2];
          sortedV[sx+2].succ = &sortedV[sx];
          sortedV[sx+2].prec = &sortedV[sx+1];
          sortedV[sx+1].prec = &sortedV[sx];
          sortedV[sx].prec = &sortedV[sx+2];
      }
      else{
          sortedV[sx].succ = &sortedV[sx+2];
          sortedV[sx+2].succ = &sortedV[sx+1];
          sortedV[sx+1].succ = &sortedV[sx];
          sortedV[sx].prec = &sortedV[sx+1];
          sortedV[sx+1].prec = &sortedV[sx+2];
          sortedV[sx+2].prec = &sortedV[sx];
      }
  }
  if(sx + 1 == dx){
          sortedV[sx].succ = &sortedV[dx];
          sortedV[sx].prec = &sortedV[dx];
          sortedV[dx].prec = &sortedV[sx];
          sortedV[dx].succ = &sortedV[sx];
      }
  if(sx == dx){
      sortedV[sx].succ = &sortedV[dx];
      sortedV[dx].prec = &sortedV[sx];
  }
}



vector<Point> ConvexHull(vector<Point> points)
{
  SortLibrary::MergeSort(points,0,points.size()-1);
  MergeHull(points,0,points.size()-1);
  vector<Point> hull = {points[0]};
  hull.reserve(points.size());
  unsigned int i = 0;
  while (*hull[i].succ != points[0])
  {hull.push_back(*hull[i++].succ);cout<<hull[i].Show()<<endl;}
  return hull;
}

}
