/* Udacity Homework 3
   HDR Tone-mapping

  Background HDR
  ==============

  A High Dynamic Range (HDR) image contains a wider variation of intensity
  and color than is allowed by the RGB format with 1 byte per channel that we
  have used in the previous assignment.  

  To store this extra information we use single precision floating point for
  each channel.  This allows for an extremely wide range of intensity values.

  In the image for this assignment, the inside of church with light coming in
  through stained glass windows, the raw input floating point values for the
  channels range from 0 to 275.  But the mean is .41 and 98% of the values are
  less than 3!  This means that certain areas (the windows) are extremely bright
  compared to everywhere else.  If we linearly map this [0-275] range into the
  [0-255] range that we have been using then most values will be mapped to zero!
  The only thing we will be able to see are the very brightest areas - the
  windows - everything else will appear pitch black.

  The problem is that although we have cameras capable of recording the wide
  range of intensity that exists in the real world our monitors are not capable
  of displaying them.  Our eyes are also quite capable of observing a much wider
  range of intensities than our image formats / monitors are capable of
  displaying.

  Tone-mapping is a process that transforms the intensities in the image so that
  the brightest values aren't nearly so far away from the mean.  That way when
  we transform the values into [0-255] we can actually see the entire image.
  There are many ways to perform this process and it is as much an art as a
  science - there is no single "right" answer.  In this homework we will
  implement one possible technique.

  Background Chrominance-Luminance
  ================================

  The RGB space that we have been using to represent images can be thought of as
  one possible set of axes spanning a three dimensional space of color.  We
  sometimes choose other axes to represent this space because they make certain
  operations more convenient.

  Another possible way of representing a color image is to separate the color
  information (chromaticity) from the brightness information.  There are
  multiple different methods for doing this - a common one during the analog
  television days was known as Chrominance-Luminance or YUV.

  We choose to represent the image in this way so that we can remap only the
  intensity channel and then recombine the new intensity values with the color
  information to form the final image.

  Old TV signals used to be transmitted in this way so that black & white
  televisions could display the luminance channel while color televisions would
  display all three of the channels.
  

  Tone-mapping
  ============

  In this assignment we are going to transform the luminance channel (actually
  the log of the luminance, but this is unimportant for the parts of the
  algorithm that you will be implementing) by compressing its range to [0, 1].
  To do this we need the cumulative distribution of the luminance values.

  Example
  -------

  input : [2 4 3 3 1 7 4 5 7 0 9 4 3 2]
  min / max / range: 0 / 9 / 9

  histo with 3 bins: [4 7 3]

  cdf : [4 11 14]


  Your task is to calculate this cumulative distribution by following these
  steps.

*/


#include "reference_calc.cpp"
#include "utils.h"

__global__
void min_kernel(const float* const d_in, float* d_out) {
	extern __shared__ float cache[];
	
	int myId = threadIdx.x + blockDim.x * blockIdx.x;
	int tid = threadIdx.x;
	cache[tid] = d_in[myId];
	__syncthreads();
	
	for(unsigned int s = blockDim.x / 2; s > 0; s >>= 1) {
		if(tid < s && d_in[myId+s] < d_in[myId]) {
			cache[myId] = cache[myId+s];
		}
		__syncthreads();
	}
	
	if(tid == 0) {
		d_out[blockIdx.x] = cache[0];
	}
}

__global__
void max_kernel(const float* const d_in, float* d_out) {
	extern __shared__ float cache[];
	
	int myId = threadIdx.x + blockDim.x * blockIdx.x;
	int tid = threadIdx.x;
	cache[tid] = d_in[myId];
	__syncthreads();
	
	for(unsigned int s = blockDim.x / 2; s > 0; s >>= 1) {
		if(tid < s && d_in[myId+s] > d_in[myId]) {
			cache[myId] = cache[myId+s];
		}
		__syncthreads();
	}
	
	if(tid == 0) {
		d_out[blockIdx.x] = cache[0];
	}
}

__global__
void generate_histo(unsigned int* histo, const float* const array, const int numBins, const int range, const int min) {
	int myId = threadIdx.x + blockIdx.x * blockDim.x;
	int myItem = array[myId];
	int myBin = (myItem - min) / range * numBins;
	atomicAdd(&(histo[myBin]), 1);
}

__global__
void scan(unsigned int* d_in, unsigned int* d_out, const int size) {
	int tid = threadIdx.x + blockIdx.x * blockDim.x;
	
	for(int offset = 1; offset < size; offset <<= 1) {
		__syncthreads();
		if(tid >= offset) {
			d_out[tid] += d_in[tid-offset];
		} else {
			d_out[tid] = d_in[tid];
		}
		__syncthreads();
	}			
}

void min(const float* const d_in, float* d_intermediate, float* d_out, const int size) {
	int threads = 1024;
	int blocks = size / threads;
	min_kernel<<<blocks, threads>>>(d_in, d_intermediate);
	threads = blocks;
	blocks = 1;
	min_kernel<<<blocks, threads>>>(d_intermediate, d_out);
}

void max(const float* const d_in, float* d_intermediate, float* d_out, const int size) {
	int threads = 1024;
	int blocks = size / threads;
	min_kernel<<<blocks, threads>>>(d_in, d_intermediate);
	threads = blocks;
	blocks = 1;
	max_kernel<<<blocks, threads>>>(d_intermediate, d_out);
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
	cudaFree(d_intermediate);
    cudaFree(d_out);
    
    cudaMalloc((void **) &d_intermediate, ARRAY_BYTES);
	cudaMalloc((void **) &d_out, sizeof(float));
	max(d_logLuminance, d_intermediate, d_out, ARRAY_SIZE);
	cudaMemcpy(&max_logLum, d_out, sizeof(float), cudaMemcpyDeviceToHost);
	cudaFree(d_intermediate);
    cudaFree(d_out);
    
    /* 2) subtract them to find the range */
    
    float logLumRange = max_logLum - min_logLum;
    
	/* 3) generate a histogram of all the values in the logLuminance channel using
       the formula: bin = (lum[i] - lumMin) / lumRange * numBins */
       
	unsigned int* d_histo = new unsigned int [numBins];
	cudaMalloc((unsigned int**) &d_histo, numBins*sizeof(unsigned int));
	generate_histo<<<blocks, threads>>>(d_histo, d_logLuminance, numBins, logLumRange, min_logLum);
	
	/* 4) Perform an exclusive scan (prefix sum) on the histogram to get
       the cumulative distribution of luminance values (this should go in the
       incoming d_cdf pointer which already has been allocated for you)       */
       
	d_cdf[0] = 0;
	for (size_t i = 1; i < numBins; ++i) {
		d_cdf[i] = d_cdf[i - 1] + d_histo[i - 1];
	}

	cudaFree(d_histo);
}
