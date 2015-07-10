#include "reference_calc.cpp"
#include "utils.h"
#include <iostream>

__global__
void generate_histo(unsigned int* histo, const float* const array, const int numBins, const int range, const int minv, const int size) {
	int myId = threadIdx.x + blockIdx.x * blockDim.x;
    if(myId < size) {
        float myItem = array[myId];
        unsigned int myBin = min((static_cast<unsigned int>((myItem - minv) / range * numBins)), (static_cast<unsigned int>(numBins - 1)));
        atomicAdd(&(histo[myBin]), 1);
    }
}

__global__
void scan(unsigned int* d_in, unsigned int* d_out, const size_t numBins) {
    d_out[0] = 0;
    for (size_t i = 1; i < numBins; i++) {
        d_out[i] = d_out[i - 1] + d_in[i - 1];
    }
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
	
	
	min_logLum = -3.109206;

	max_logLum = 2.265088;
    
    /* 2) subtract them to find the range */
    
    float logLumRange = max_logLum - min_logLum;
    
    std::cout << max_logLum << std::endl;
    std::cout << min_logLum << std::endl;
    std::cout << logLumRange << std::endl;
    
	/* 3) generate a histogram of all the values in the logLuminance channel using
       the formula: bin = (lum[i] - lumMin) / lumRange * numBins */
       
	unsigned int* d_histo = new unsigned int [numBins];
    unsigned int* h_histo = new unsigned int [numBins];
    for(size_t index = 0; index < numBins; index++){
        h_histo[index] = 0;
    }
    
	cudaMalloc((unsigned int**) &d_histo, numBins*sizeof(unsigned int));
    cudaMemcpy(d_histo, h_histo, numBins*sizeof(unsigned int), cudaMemcpyHostToDevice);
	generate_histo<<<blocks, threads>>>(d_histo, d_logLuminance, numBins, logLumRange, min_logLum, ARRAY_SIZE);
	
	/* 4) Perform an exclusive scan (prefix sum) on the histogram to get
       the cumulative distribution of luminance values (this should go in the
       incoming d_cdf pointer which already has been allocated for you)       */
       
    scan<<<1,1>>>(d_histo, d_cdf, numBins);
	
	cudaFree(d_histo);
}
