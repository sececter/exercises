//Udacity HW 4
//Radix Sorting

#include "reference_calc.cpp"
#include "utils.h"

__global__ 
void generate_histo(unsigned int* d_vals_src, unsigned int* d_histo, unsigned int numBins, unsigned int i, const size_t numElems)
{
	unsigned int mask = (numBins - 1) << i;
	for (unsigned int j = 0; j < numElems; ++j) {
		unsigned int bin = (d_vals_src[j] & mask) >> i;
		d_histo[bin]++;
    }
}

__global__
void scan(unsigned int* d_histo, unsigned int* d_scan, unsigned int numBins)
{
	for (unsigned int j = 1; j < numBins; ++j) 
	{
		d_scan[j] = d_scan[j - 1] + d_histo[j - 1];
	}
}

__global__
void write(unsigned int* d_inputVals, unsigned int* d_outputVals, unsigned int* d_inputPos, unsigned int* d_outputPos, unsigned int* d_scan, unsigned int i, unsigned int numBins, const size_t numElems)
{
	unsigned int mask = (numBins - 1) << i;
	for (unsigned int j = 0; j < numElems; ++j) {
		unsigned int bin = (d_inputVals[j] & mask) >> i;
		d_outputVals[d_scan[bin]] = d_inputVals[j];
		d_outputPos[d_scan[bin]]  = d_outputPos[j];
		d_scan[bin]++;
	}
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
	const int numBits = 1;
	const int numBins = 1 << numBits;
	const int elemsPerBlock = 512;
	const int numBlocks = numElems / elemsPerBlock;

	unsigned int *d_histo;
	unsigned int *d_scan;
	cudaMalloc((unsigned int**) &d_histo, numBins*sizeof(unsigned int));
	cudaMalloc((unsigned int**) &d_scan, numBins*sizeof(unsigned int));

	unsigned int *d_vals_src = d_inputVals;
	unsigned int *d_pos_src  = d_inputPos;

	unsigned int *d_vals_dst = d_outputVals;
	unsigned int *d_pos_dst  = d_outputPos;
	
	unsigned int swaps = 0;
	
	for (unsigned int i = 0; i < 8 * sizeof(unsigned int); i += numBits)
	{		
		cudaMemset(d_histo, 0, numBins*sizeof(unsigned int));
		cudaMemset(d_scan, 0, numBins*sizeof(unsigned int)); 	
		
		generate_histo<<<1,1>>>(d_vals_src, d_histo, numBins, i, numElems);
		
		scan<<<1,1>>>(d_histo, d_scan, numBins);

		write<<<1,1>>>(d_vals_src, d_vals_dst, d_pos_src, d_pos_dst, d_scan, i, numBins, numElems);
		
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



