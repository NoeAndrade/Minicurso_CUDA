#include <stdio.h>

#include <cuda_runtime.h>
#include "cuda_Error.cuh"
__global__ void vectorSuma(double *A, double *B, double *C, int numElements) //Definiendo el Kernel
{
  int i = blockDim.x * blockIdx.x + threadIdx.x;

  if (i >= numElements)return; //Los hilos que no son menores que numElements no realizan los siguientes calculos

  C[i] = A[i] + B[i];
}


int main()
{
    cudaError_t err = cudaSuccess;
    double *h_A,*h_B,*h_C,*d_A,*d_B,*d_C; //arreglos

    int N=100; //numero de elementos que contiene el arreglo

    h_A = new double[N];
    h_B = new double[N];
    h_C = new double[N];

    size_t size=sizeof(double)*N; //numero de bytes que requiero para los arreglos

    //comprobando que la asignación de memoria de los arreglos en el Host fue exitosa
    if (h_A == NULL || h_B == NULL || h_C == NULL) {
        fprintf(stderr, "No se pudo asignar memoria para los vectores en el host !\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i<N; ++i) {
        h_A[i] = rand() / (double)RAND_MAX;
        h_B[i] = rand() / (double)RAND_MAX;
        
    }
    //El segundo parametro del Errorcuda es 0 ya que este corresponde a reviasr si se asigna memoria con cudaMalloc correctamente.
    Errorcuda(cudaMalloc(&d_A, size),0,"d_A"); 
    Errorcuda(cudaMalloc(&d_B, size),0,"d_B"); 
    Errorcuda(cudaMalloc(&d_C, size),0,"d_C"); 

    //Se copia la información que se asigno en el Host a h_A y h_B y se copia en la memoria global de la GPU en d_A y d_B respectivamente
    Errorcuda(cudaMemcpy(d_A, h_A, size, cudaMemcpyHostToDevice),1,"h_A");
    Errorcuda(cudaMemcpy(d_B, h_B, size, cudaMemcpyHostToDevice),1,"h_B");
       
    int threadsPerBlock = 256;
    int blocksPerGrid = (N + threadsPerBlock - 1) / threadsPerBlock;

    vectorSuma<<<blocksPerGrid, threadsPerBlock>>>(d_A, d_B, d_C, N);
    err = cudaGetLastError();
  
    Errorcuda(err,3,"vectorSuma");
    
    Errorcuda(cudaMemcpy(h_C, d_C, size, cudaMemcpyDeviceToHost),2,"d_C");
    //Las operaciones de cudaMemcpy sincronizan el device por lo que no es necesario usar cudadeviceSynchronize()
    
    Errorcuda(cudaFree(d_A),4,"d_A");
    Errorcuda(cudaFree(d_B),4,"d_B");
    Errorcuda(cudaFree(d_C),4,"d_C");
    
    for (int i = 0; i < N; ++i) {
      fprintf(stderr, "h_A[%d]: %f, h_B[%d]: %f, h_C[%d]: %f\n", i,h_A[i], i,h_B[i], i,h_C[i]);
    }

    delete[] h_A;
    delete[] h_B;
    delete[] h_C;  

    return 0;

}
