#include "Delaunay.hpp"

int main()
{
  ProjectLibrary::Delaunay mainDelaunay;
  mainDelaunay.importMesh("./Test2.csv");
  //mainDelaunay.maxAreaTriangle();


  mainDelaunay.triangulate();
  mainDelaunay.exportPoints("./ProvaPoints.csv");
  mainDelaunay.exportSegments("./ProvaSegs.csv");

// del.Show()

  return 0;
}
