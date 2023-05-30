#ifndef __SORTING_H
#define __SORTING_H

#include "iostream"
#include "list"
#include "Eigen/Eigen"
#include "map"

using namespace std;
using namespace Eigen;

namespace SortLibrary {

  template<typename T>
  void Merge(vector<T>& v,
             const unsigned int& sx,
             const unsigned int& cx,
             const unsigned int& dx){
      unsigned int i = sx; unsigned int j = cx +1; unsigned int k = 0;
      vector<T> mergedV(v.size());
      while( (i<=cx) && (j<=dx) ){
        if (v[i] <= v[j]){
            mergedV[k] = v[i++];
        }
        else{
            mergedV[k]=v[j++];
        }
        k++;
      }
      while (i<=cx){
          mergedV[k++] = v[i++];
      }
      while (j <= dx){
          mergedV[k++] = v[j++];
      }
      for (unsigned int i = sx; i <= dx; i++){
          v[i] = mergedV[i-sx];
      }

  }

  template<typename T>
  void MergeSort(vector<T>& v,
                 const unsigned int& sx,
                 const unsigned int& dx){
    if (sx < dx)
    {
        int cx = (sx+dx)/2;
        MergeSort(v,sx,cx);
        MergeSort(v,cx+1,dx);
        Merge(v,sx,cx,dx);
    }
  }

}

#endif // __SORTING_H
