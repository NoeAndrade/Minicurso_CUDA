//cuda libraries//
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <stdio.h>
//kernel para la suma de vectores
__global__ void unique_idx_calc_threadIdx(int * input)
{
	int tid = threadIdx.x;
	printf("threadIdx : %d, value : %d \n" ,tid, input[tid]);

}

__global__ void unique_gid_calculation(int * input)
{
	int tid = threadIdx.x;
	int offset = blockIdx.x * blockDim.x;
	int gid = tid + offset;
	printf("blockIdx : %d, threadIdx : %d ,gid : %d, value : %d \n",blockIdx.x, tid,gid,input[gid]);

}



// main suma de vectores
int main()
{
	int array_size = 16;
	int array_byte_size = sizeof(int) * array_size;
	int h_data[] = {23,9,4,53,65,12,1,33,11,12,13,14,15,16,17,18};

	for (int i=0; i < array_size; i++)
	{
		printf("%d ",h_data[i]);			
	}
	printf("\n \n");
	
	int * d_data;
	cudaMalloc((void**)&d_data, array_byte_size);
	cudaMemcpy(d_data,h_data, array_byte_size , cudaMemcpyHostToDevice);

	dim3 block(4);
	dim3 grid(2,2);

	unique_gid_calculation <<< grid, block >>> (d_data);

	cudaDeviceSynchronize();
	cudaDeviceReset();
	return 0;
}


