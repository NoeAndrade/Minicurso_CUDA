#include <stdio.h>

#include <cuda_runtime.h>

__global__ void vectorSuma(double *A, double *B, double *C,
                          int numElements) {
  int i = blockDim.x * blockIdx.x + threadIdx.x;

  if (i < numElements) {
    C[i] = A[i] + B[i];
  }
}


int main()
{
    cudaError_t err = cudaSuccess;
    double *h_A,*h_B,*h_C,*d_A,*d_B,*d_C;
    int N=100;
    h_A=new double[N];
    h_B=new double[N];
    h_C=new double[N];
    int size=sizeof(double)*N;

    if (h_A == NULL || h_B == NULL || h_C == NULL) {
        fprintf(stderr, "Failed to allocate host vectors!\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i<N; ++i) {
        h_A[i] = rand() / (double)RAND_MAX;
        h_B[i] = rand() / (double)RAND_MAX;
        
    }

    err = cudaMalloc((void **)&d_A, size);

    if (err != cudaSuccess) {
      fprintf(stderr, "Failed to allocate device vector A (error code %s)!\n",
              cudaGetErrorString(err));
      exit(EXIT_FAILURE);
    }
    err = cudaMalloc((void **)&d_B, size);

    if (err != cudaSuccess) {
      fprintf(stderr, "Failed to allocate device vector A (error code %s)!\n",
              cudaGetErrorString(err));
      exit(EXIT_FAILURE);
    }
    err = cudaMalloc((void **)&d_C, size);

    if (err != cudaSuccess) {
      fprintf(stderr, "Failed to allocate device vector A (error code %s)!\n",
              cudaGetErrorString(err));
      exit(EXIT_FAILURE);
    }
    err = cudaMemcpy(d_A, h_A, size, cudaMemcpyHostToDevice);

    if (err != cudaSuccess) {
      fprintf(stderr,
              "Failed to copy vector A from host to device (error code %s)!\n",
              cudaGetErrorString(err));
      exit(EXIT_FAILURE);
    }
  
    err = cudaMemcpy(d_B, h_B, size, cudaMemcpyHostToDevice);
  
    if (err != cudaSuccess) {
      fprintf(stderr,
              "Failed to copy vector B from host to device (error code %s)!\n",
              cudaGetErrorString(err));
      exit(EXIT_FAILURE);
    }
       
    int threadsPerBlock = 256;
    int blocksPerGrid = (N + threadsPerBlock - 1) / threadsPerBlock;

    vectorSuma<<<blocksPerGrid, threadsPerBlock>>>(d_A, d_B, d_C, N);
    err = cudaGetLastError();
  
    if (err != cudaSuccess) {
      fprintf(stderr, "Failed to launch vectorAdd kernel (error code %s)!\n",
              cudaGetErrorString(err));
      exit(EXIT_FAILURE);
    }
    
    err = cudaMemcpy(h_C, d_C, size, cudaMemcpyDeviceToHost);
  
    if (err != cudaSuccess) {
      fprintf(stderr,
              "Failed to copy vector B from host to device (error code %s)!\n",
              cudaGetErrorString(err));
      exit(EXIT_FAILURE);
    }

    for (int i = 0; i < N; ++i) {
        fprintf(stderr, "h_A[%d]: %f, h_B[%d]: %f, h_C[%d]: %f\n", i,h_A[i], i,h_B[i], i,h_C[i]);
      }
return 0;

}
