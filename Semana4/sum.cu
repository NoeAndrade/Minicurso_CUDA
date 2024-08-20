#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//for memset
#include <cstring>


__global__ void sum_array(int * a, int * b, int * c, int size)
{
	int gid = blockIdx.x * blockDim.x +threadIdx.x;

	if (gid < size)
	{
		c[gid] =a[gid] + b[gid];
	}

}

int main(){
	int size = 10000;
	int block_size = 128;

	int NO_BYTES = size * sizeof(int);

	//host pointers
	int* h_a, *h_b, *gpu_results;

	h_a = (int*)malloc(NO_BYTES);
	h_b = (int*)malloc(NO_BYTES);
	gpu_results = (int*)malloc(NO_BYTES);


	//Inicializamos host pointer
	time_t t;
	srand((unsigned)time(&t));
	for (int i = 0;i<size;i++)
	{
		h_a[i] = (int)(rand() & 0xFF);
	}
	for (int i = 0;i<size;i++)
        {               
                h_b[i] = (int)(rand() & 0xFF);
        }

	memset(gpu_results,0,NO_BYTES);

	//Device pointer
	int* d_a, *d_b, *d_c;
	cudaMalloc((int **)&d_a, NO_BYTES);
	cudaMalloc((int **)&d_b, NO_BYTES);
	cudaMalloc((int **)&d_c, NO_BYTES);
	//Transferencia de memoria from host to device
	cudaMemcpy(d_a, h_a,NO_BYTES,cudaMemcpyHostToDevice);
	cudaMemcpy(d_b, h_b,NO_BYTES,cudaMemcpyHostToDevice);
	
	//lanzamos el grid
	dim3 block(block_size);
	dim3 grid((size/block.x)+1);
	
	sum_array<<<grid,block>>> (d_a,d_b,d_c,size);
	cudaDeviceSynchronize();


	cudaMemcpy(gpu_results, d_c,NO_BYTES,cudaMemcpyDeviceToHost);
	for (int i=0;i<size;i++)
	{

	printf("C[%d] : %d \n",i,gpu_results[i]);
	}
}




