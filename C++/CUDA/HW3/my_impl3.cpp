#include "reference_calc.cpp"
#include "utils.h"
#include "float.h"
#include "math.h"
#include <iostream>

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

__global__
void find_minmax(float* min_logLum, float* max_logLum, const float* const d_logLuminance, const int size) {
	float logLumMin = d_logLuminance[0];
	float logLumMax = d_logLuminance[0];

	for (size_t i = 1; i < size; ++i) {
		logLumMin = min(d_logLuminance[i], logLumMin);
		logLumMax = max(d_logLuminance[i], logLumMax);
	}
	*min_logLum = logLumMin;
    *max_logLum = logLumMax;
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
	
	find_minmax<<<1,1>>>(min_logLum, max_logLum, ARRAY_SIZE);
    
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
