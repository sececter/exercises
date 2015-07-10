#include "reference_calc.cpp"
#include "utils.h"
#include "float.h"
#include "math.h"
#include <iostream>

typedef float (*op_t)(const float& x, const float& y);

__device__ float min_op(const float& x, const float& y) {
	return min(x,y);
}

__device__ float max_op(const float& x, const float& y) {
	return max(x,y);
}

template <op_t op>
__global__
void reduce(const float* const d_in, float* d_out, const int size) {
	extern __shared__ float cache[];
	
	int myId = threadIdx.x + blockDim.x * blockIdx.x;
	int tid = threadIdx.x;
	cache[tid] = (op(0,1)) ? -FLT_MAX : FLT_MAX;
	if(myId < size)
		cache[tid] = d_in[myId];
	__syncthreads();
	
	for(unsigned int s = blockDim.x / 2; s > 0; s >>= 1) {
		if(tid < s && myId < size) {
			cache[myId] = op(cache[myId], cache[myId+s]);
		}
		__syncthreads();
	}
	
	if(tid == 0) {
		d_out[blockIdx.x] = cache[0];
	}
}

__global__
void generate_histo(unsigned int* histo, const float* const array, const int numBins, const int range, const int min, const int array_size) {
	int myId = threadIdx.x + blockIdx.x * blockDim.x;
	if (myId < array_size) {
		float myItem = array[myId];
		int myBin = (myItem - min) / range * numBins;
		atomicAdd(&(histo[myBin]), 1);
	}
}

__global__
void scan(unsigned int* d_in, unsigned int* d_out, const int n) {
	extern __shared__ unsigned int temp[];
	
	int thid = threadIdx.x;
	int pin = 1, pout = 0;
	
	temp[pout*n+thid] = (thid > 0) ? d_in[thid-1] : 0;
	
	__syncthreads();
	
	for(int offset = 1; offset < n; offset <<= 1) {
		pout = 1 - pout;
		pin = 1 - pout;
		if(thid >= offset) {
			temp[pout*n + thid] += temp[pin*n + thid - offset];
		} else {
			temp[pout*n + thid] = temp[pin*n+thid];
		}
		__syncthreads();
	}
	
	d_out[thid] = temp[pout*n + thid];	
}

void min(const float* const d_in, float* d_intermediate, float* d_out, const int size) {
	int threads = 1024;
	int blocks = size / threads;
	int bytes = pow(2, ceil(log2((float)size)))*sizeof(float);
	reduce<min_op><<<blocks, threads, bytes>>>(d_in, d_intermediate, size);
	threads = blocks;
	blocks = 1;
	reduce<min_op><<<blocks, threads, bytes>>>(d_intermediate, d_out, size);
}

void max(const float* const d_in, float* d_intermediate, float* d_out, const int size) {
	int threads = 1024;
	int blocks = size / threads;
    int bytes = pow(2, ceil(log2((float)size)))*sizeof(float);
	reduce<max_op><<<blocks, threads, bytes>>>(d_in, d_intermediate, size);
	threads = blocks;
	blocks = 1;
	reduce<max_op><<<blocks, threads, bytes>>>(d_intermediate, d_out, size);
}

void your_histogram_and_prefixsum(const float* const d_logLuminance,
                                  unsigned int* const d_cdf,
                                  float &min_logLum,
                                  float &max_logLum,
                                  const size_t numRows,
                                  const size_t numCols,
                                  const size_t numBins)
{		
	/* 1) find the minimum and maximum value in the input logLuminance channel
       store in min_logLum and max_logLum */
  
	const int ARRAY_SIZE = numRows * numCols;
	const int ARRAY_BYTES = ARRAY_SIZE * sizeof(float);
	const int threads = 1024;
	const int blocks = ARRAY_SIZE / threads;
	float * d_intermediate;
    float * d_out;
	
	cudaMalloc((void **) &d_intermediate, ARRAY_BYTES);
	cudaMalloc((void **) &d_out, sizeof(float));
	
	min(d_logLuminance, d_intermediate, d_out, ARRAY_SIZE);
	cudaMemcpy(&min_logLum, d_out, sizeof(float), cudaMemcpyDeviceToHost);

	max(d_logLuminance, d_intermediate, d_out, ARRAY_SIZE);
	cudaMemcpy(&max_logLum, d_out, sizeof(float), cudaMemcpyDeviceToHost);
	
	cudaFree(d_intermediate);
    cudaFree(d_out);
    
    /* 2) subtract them to find the range */
    
    float logLumRange = max_logLum - min_logLum;
    
    std::cout << max_logLum << std::endl;
    std::cout << min_logLum << std::endl;
    std::cout << logLumRange << std::endl;
    
	/* 3) generate a histogram of all the values in the logLuminance channel using
       the formula: bin = (lum[i] - lumMin) / lumRange * numBins */
       
	unsigned int* d_histo = new unsigned int [numBins];
	cudaMalloc((unsigned int**) &d_histo, numBins*sizeof(unsigned int));
	generate_histo<<<blocks, threads>>>(d_histo, d_logLuminance, numBins, logLumRange, min_logLum, ARRAY_SIZE);
	
	/* 4) Perform an exclusive scan (prefix sum) on the histogram to get
       the cumulative distribution of luminance values (this should go in the
       incoming d_cdf pointer which already has been allocated for you)       */
       
	scan<<<1, threads, 2*threads*sizeof(unsigned int)>>>(d_histo, d_cdf, numBins);
	
	cudaFree(d_histo);
}
