#include "Delaunay.hpp"

int main()
{
  ProjectLibrary::Delaunay mainDelaunay;
  mainDelaunay.importMesh("C:/Users/aless/Desktop/PCS/PCS2023_Exercises/Projects/Delaunay/Dataset/Test2.csv");
  mainDelaunay.triangulate();
  //mainDelaunay.exportPoints("C:/Users/aless/Desktop/PCS/PCS2023_Exercises/Projects/Delaunay/Dataset/ProvaPoints.csv");
  //mainDelaunay.exportSegments("C:/Users/aless/Desktop/PCS/PCS2023_Exercises/Projects/Delaunay/Dataset/ProvaSegs.csv");

// del.Show()

  return 0;
}
