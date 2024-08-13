#include <iostream>
#include <stdlib.h>
#include <stdio.h>
void sumav(double *A,double *B,double *C,int tam)
{
  int i;
  for(i=0;i<tam;i++){
    C[i]=A[i]+B[i];
  }
}
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

  for(i=0;i<tamVec;i++){
    A[i]=100*((double)rand()/ RAND_MAX);
    B[i]=100*((double)rand()/ RAND_MAX);
  }
  for(i=0;i<tamVec;i++){
    printf("A[%d]: %lf\n",i,A[i]);
    printf("B[%d]: %lf\n",i,B[i]);
  }
  sumav(A,B,C,tamvec);
  for(i=0;i<tamVec;i++){
    printf("C[%d]: %lf\n",i,C[i]);
  }
  delete[] A;
  delete[] B;
  delete[] C;
  
  return 0;
}
