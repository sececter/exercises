#include "utils.h"
#include "reference.cpp"

const unsigned int threadsPerBlock = 256;
const unsigned int elemsPerThread = 16;
const unsigned int elemsPerBlock = threadsPerBlock * elemsPerThread;


__global__
void yourHisto(const unsigned int* const vals, //INPUT
               unsigned int* const histo,      //OUPUT
               int numVals)
{
    int tid = blockIdx.x*blockDim.x + threadIdx.x;
    int valsPerThread = numVals/elemsPerThread;
    
    extern __shared__ unsigned int local[];
    
    for(int i = 0; i < elemsPerThread && threadIdx.x + i*valsPerThread < numVals; i++)
        local[threadIdx.x + i*valsPerThread] = 0;
    __syncthreads();
    
    for(int i = tid*elemsPerThread; i < tid*elemsPerThread + elemsPerThread; i++) {
        atomicAdd(&local[vals[i]],1);
    }
    __syncthreads();
    
    for(int i = threadIdx.x*valsPerThread; i < threadIdx.x*valsPerThread + valsPerThread && i < numVals; i++)
        atomicAdd(&histo[i], local[i]);
}

void computeHistogram(const unsigned int* const d_vals, //INPUT
                      unsigned int* const d_histo,      //OUTPUT
                      const unsigned int numBins,
                      const unsigned int numElems)
{
    yourHisto<<<numElems/elemsPerBlock, threadsPerBlock, numBins*sizeof(unsigned int)>>>(d_vals, d_histo, numBins);

  cudaDeviceSynchronize(); checkCudaErrors(cudaGetLastError());
}
