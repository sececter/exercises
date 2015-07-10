#include "utils.h"
#include "reference.cpp"

const unsigned int threadsPerBlock = 256;
const unsigned int elemsPerThread = 16;
const unsigned int elemsPerBlock = threadsPerBlock * elemsPerThread;


__global__
void yourHisto(const unsigned int* const vals, //INPUT
               unsigned int* const histo,      //OUPUT
               int numBins,
               unsigned int numElems)
{
    int tid = blockIdx.x*blockDim.x + threadIdx.x;
    int binsPerThread = numBins/elemsPerThread;
    int offset = blockDim.x * gridDim.x;
    
    extern __shared__ unsigned int local[];
    
    for(int i = 0; i < elemsPerThread && threadIdx.x + i*binsPerThread < numVals; i++)
        local[threadIdx.x + i*binsPerThread] = 0;
    __syncthreads();
    
    for(int i = tid; i < numElems; i += offset) {
        atomicAdd(&local[vals[i]],1);
    }
    __syncthreads();
    
    for(int i = 0; i < elemsPerThread && threadIdx.x + i*binsPerThread < numVals; i++)
        atomicAdd(&histo[threadIdx.x + i*binsPerThread], local[threadIdx.x + i*binsPerThread]);
}

void computeHistogram(const unsigned int* const d_vals, //INPUT
                      unsigned int* const d_histo,      //OUTPUT
                      const unsigned int numBins,
                      const unsigned int numElems)
{
    yourHisto<<<numElems/elemsPerBlock, threadsPerBlock, numBins*sizeof(unsigned int)>>>(d_vals, d_histo, numBins, numElems);

  cudaDeviceSynchronize(); checkCudaErrors(cudaGetLastError());
}
