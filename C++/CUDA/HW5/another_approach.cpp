#include "utils.h"
#include "reference.cpp"

const unsigned int threadsPerBlock = 256;
const unsigned int elemsPerThread = 16;
const unsigned int elemsPerBlock = threadsPerBlock * elemsPerThread;

__global__
void yourHisto(const unsigned int* const vals, //INPUT
               unsigned int* const histo,      //OUPUT
               int size)
{
	__shared__ unsigned int temp[1024];
  
     temp[threadIdx.x + 0] = 0;
     temp[threadIdx.x + 256] = 0;
     temp[threadIdx.x + 512] = 0;
     temp[threadIdx.x + 768] = 0;
     __syncthreads();

     int i = threadIdx.x + blockIdx.x * blockDim.x;
     int offset = blockDim.x * gridDim.x;
     while (i < size)
     {
              atomicAdd( &temp[vals[i]], 1);
              i += offset;
     }
     __syncthreads();


  
    atomicAdd( &(histo[threadIdx.x + 0]), temp[threadIdx.x + 0] );
    atomicAdd( &(histo[threadIdx.x + 256]), temp[threadIdx.x + 256] );
    atomicAdd( &(histo[threadIdx.x + 512]), temp[threadIdx.x + 512] );
    atomicAdd( &(histo[threadIdx.x + 768]), temp[threadIdx.x + 768] );
}

void computeHistogram(const unsigned int* const d_vals, //INPUT
                      unsigned int* const d_histo,      //OUTPUT
                      const unsigned int numBins,
                      const unsigned int numElems)
{
  yourHisto<<<numElems/elemsPerBlock, threadsPerBlock, numBins*sizeof(unsigned int)>>>(d_vals, d_histo, numElems);
	
  cudaDeviceSynchronize(); checkCudaErrors(cudaGetLastError());
}
