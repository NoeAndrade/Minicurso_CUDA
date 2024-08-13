#include <iostream>

int main()
{
  double *A;
  double *B;
  double *C;
  int tamVec=10;
  //version en c
  /*
  A=(*double)malloc(tamVec*sizeof(double));
  B=(*double)malloc(tamVec*sizeof(double));
  C=(*double)malloc(tamVec*sizeof(double));
  free( A );
  free( B );
  free( C );
  */
  version en c++
  A = new double[tamVec];
  B = new double[tamVec];
  C = new double[tamVec];
  delete[] A;
  delete[] B;
  delete[] C;
  
  return 0;
}
