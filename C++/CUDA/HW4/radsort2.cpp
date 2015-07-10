//Udacity HW 4
//Radix Sorting

#include "reference_calc.cpp"
#include "utils.h"
#include <thrust/scan.h>

__global__ 
void generate_histo(unsigned int* d_vals_src, unsigned int* d_histo, unsigned int numBins, unsigned int i)
{
	unsigned int src_idx = threadIdx.x + blockIdx.x * blockDim.x;
	unsigned int mask = (numBins - 1) << i;
	unsigned int bin = (d_vals_src[src_idx] & mask) >> i;
	unsigned int histo_scan_idx = blockIdx.x + bin * gridDim.x; 
	atomicAdd(&(d_histo[histo_scan_idx]), 1);
}

__global__
void write(unsigned int* d_vals_src, unsigned int* d_pos_src, unsigned int* d_vals_dst, unsigned int* d_pos_dst, 
													unsigned int* d_scan, unsigned int numBins, unsigned int i)
{
	unsigned int src_idx = threadIdx.x + blockIdx.x * blockDim.x;
	unsigned int mask = (numBins - 1) << i;
	unsigned int bin = (d_vals_src[src_idx] & mask) >> i;
	unsigned int histo_scan_idx = blockIdx.x + bin * gridDim.x;
	//We have to find this elements location within its bin
	unsigned int loc_pos = 0;
	for(int i = 0; i < threadIdx.x; i++)
	{
		if((d_vals_src[blockIdx.x * blockDim.x + i] & mask) >> i == bin)
			loc_pos++;
	}
	unsigned int pos = d_scan[histo_scan_idx] + loc_pos;
	d_vals_dst[pos] = d_vals_src[src_idx];
	d_pos_dst[pos] = d_pos_src[src_idx];
}

__global__
void copy(unsigned int* d_outputVals, unsigned int* d_outputPos, unsigned int* d_inputVals, unsigned int* d_inputPos)
{
	unsigned int src_idx = threadIdx.x + blockIdx.x * blockDim.x;
	d_outputVals[src_idx] = d_inputVals[src_idx];
	d_outputPos[src_idx] = d_inputPos[src_idx];
}
void your_sort(unsigned int* const d_inputVals,
               unsigned int* const d_inputPos,
               unsigned int* const d_outputVals,
               unsigned int* const d_outputPos,
               const size_t numElems)
{
	const int numBits = 4;
	const int numBins = 1 << numBits;
	const int elemsPerBlock = 64;
	const int numBlocks = numElems / elemsPerBlock;

	unsigned int *d_histo;
	unsigned int *d_scan;
	cudaMalloc((unsigned int**) &d_histo, numBlocks*numBins*sizeof(unsigned int));
	cudaMalloc((unsigned int**) &d_scan, numBlocks*numBins*sizeof(unsigned int));

	unsigned int *d_vals_src = d_inputVals;
	unsigned int *d_pos_src  = d_inputPos;

	unsigned int *d_vals_dst = d_outputVals;
	unsigned int *d_pos_dst  = d_outputPos;
	
	unsigned int swaps = 0;
	
	for (unsigned int i = 0; i < 8 * sizeof(unsigned int); i += numBits)
	{		
		cudaMemset(d_histo, 0, numBlocks*numBins*sizeof(unsigned int));
		cudaMemset(d_scan, 0, numBlocks*numBins*sizeof(unsigned int)); 	
		
		//Generate bucket histo for each block, output d_histo table
		generate_histo<<<numBlocks, elemsPerBlock>>>(d_vals_src, d_histo, numBins, i);
		
		//Generate global offsets for each bucket by scanning histo
		//scan<<<numBlocks, elemsPerBlock, 2*numBlocks*numBins*sizeof(unsigned int)>>>(d_histo, d_scan, numBlocks*numBins);
		thrust::exclusive_scan(d_histo, d_histo+numBlocks*numBins, d_scan);
		
		//Calculate global offset for each elem and write
		write<<<numBlocks, elemsPerBlock>>>(d_vals_src, d_pos_src, d_vals_dst, d_pos_dst, d_scan, numBins, i);
		
		std::swap(d_vals_dst, d_vals_src);
		std::swap(d_pos_dst, d_pos_src);
		swaps++;
	}
	
	if(swaps % 2 == 0) 
	{
		copy<<<numBlocks, elemsPerBlock>>>(d_outputVals, d_outputPos, d_inputVals, d_inputPos);
	}
	
	cudaFree(d_histo);
	cudaFree(d_scan);
}

