//Udacity HW 4
//Radix Sorting

#include "reference_calc.cpp"
#include "utils.h"
 
//This unnecesarily complicated
 
//Returns the position of calling thread in block-sorted array
__device__ unsigned int split(bool pred, unsigned int blocksize, unsigned int* shmem)
{
	//Count the number of true predicates held by lower numbered threads
	unsigned int true_before = reduce(pred, shmem);
	
	//If last thread, calculate total number of false predicates
	__shared__ unsigned int false_total;
	if(threadIdx.x == blocksize - 1)
		false_total = blocksize - (true_before + pred)
	__syncthreads();
	
	//Return the position of this thread in block-sorted array
	//First false, then true
	if(pred) 	return true_before - 1 + false_total;
	else 		return threadIdx.x - true_before;
}

//Returns true if i to i+b-th (right to left) bits are different
__device__ bool different(unsigned int a, unsigned int b, unsigned int from_bit, unsigned int bits)
{
	unsigned int xored = (a >> i) ^ (b >> i);
	//Now we have to check last bits bit of xored - if not all zero, different
	//If not divisible by 2^b, 
	if(~xored % (1 << bits) != 0)
		return false;
	else return true;
}

//Sort each block in on-chip memory by last b digits
//We want to keep track of number of elements in each of 2^b bins while
//sorting
__global__
void sort_blocks(unsigned int* d_inputVals, unsigned int* d_out, unsigned int* d_inputPos, unsigned int* d_histo, unsigned int* d_offsets, const size_t numElems, unsigned int i, const unsigned int b)
{	
	//Each knows its start via blockIdx.x, has to calculate its blocksize 
	//using passed numElems and blockDim
	unsigned int blocksize = (blockIdx.x == gridDim.x) ? numElems - blockDim.x * (gridDim.x - 1) : numElems / blockDim.x;
	unsigned int tid = threadIdx.x;
	unsigned int myId = threadIdx.x + blockIdx.x * blockDim.x;
	unsigned int numBins = (1 << b);
	
	//Load block to shared memory
	extern __shared__ unsigned int shmem[] = d_inputVals + (blockIdx.x - 1) * numElems / blockDim.x;
	
	//Perform splitting b-times
	for(int j = 0; j < b; j++) 
	{
		bool current_bit = (shmem[tid] >> (j+i)) & 1;
		predicates[tid] = current_bit;
		__syncthreads();
		unsigned int thread_pos = split(current_bit, blocksize);
		unsigned int thread_val = shmem[tid];
		__syncthreads();
		shmem[thread_pos] = thread_val;
		__syncthreads();
	}
	
	//If this thread's element radix digit (those b bits) differ from its
	//neighbor, save its threadIdx.x to an array of size 2^b, this is its
	//bucket offset
	unsigned int mask = (numBins - 1) << i;
	unsigned int bin = numBins * blockIdx.x + ((shmem[tid] & mask) >> i);
	if (tid == 0) d_offsets[0] = 0;			//OFfset of first bucket is zero
	if(tid > 0 && different(shmem[tid], shmem[tid-1], i, b))
	{
		d_offsets[bin] = tid;
	}
	
	__syncthreads();
	
	//First thread of each bin will calculate the offset difference with
	//the next bin
	//Then save this value to proper place in global histogram
	if(tid == d_offsets[bin] && bin+1 < numBins)
	{
		d_histo[blockIdx.x * numBins + bin] = d_offsets[bin+1] - d_offsets[bin];
	}
	
	//Need to output sorted array
	d_out[myId] = shmem[tid];
}

//Calculate the final location in output array for each element in the
//input array from its bucket positions global offset and its local position
//in the bucket and write to output
__global__
void write(unsigned int* d_in, unsigned int* d_out, unsigned int* d_histo, unsigned int* d_offsets, const unsigned int b, unsigned int i, const unsigned int numBins)
{
	unsigned int myId = threadIdx.x + blockIdx.x * blockDim.x;
	unsigned int mask = (numBins - 1) << i;
	unsigned int bin = (d_in[myId] & mask) >> i;
	unsigned int histo_idx = blockIdx.x * numBins + bin;
	unsigned int bin_pos = threadIdx.x - d_offsets[myId];
	unsigned int fin_pos = d_histo[histo_idx] + bin_pos;
	d_out[fin_pos] = d_in[myId];
}


__global__
void scan(unsigned int* d_in, const int n) {
	extern __shared__ unsigned int temp[];
	
	int thid = threadIdx.x;
	int pin = 1, pout = 0;
	
	temp[pout*n+thid] = (thid > 0) ? d_in[thid-1] : 0;
	
	__syncthreads();
	
	for(int offset = 1; offset < n; offset <<= 1) {
		pout = 1 - pout;
		pin = 1 - pout;
		if(thid >= offset) {
			temp[pout*n + thid] = temp[pin*n + thid] + temp[pin*n + thid - offset];
		} else {
			temp[pout*n + thid] = temp[pin*n+thid];
		}
		__syncthreads();
	}
	
	__syncthreads();
	d_in[thid] = temp[pout*n + thid];	
}

void your_sort(unsigned int* const d_inputVals,
               unsigned int* const d_inputPos,
               unsigned int* const d_outputVals,
               unsigned int* const d_outputPos,
               const size_t numElems)
{	
	//Calculate the number of blocks, give each block say 1024 threads
	const unsigned int b = 1;
	const unsigned int numBins = 1 << b;
	const size_t elemsPerBlock = 1024;
	const size_t numBlocks = numElems / elemsPerBlock + 1;
	const size_t histoSize = numBlocks*numBins;
	const size_t histoBytes = histoSize * sizeof(unsigned int);
	
	unsigned int* d_in = d_inputVals;
	unsigned int* d_out = d_outputVals;
	
	//Histogram column order table will be created on device global memory
	unsigned int* d_histo;
	//Offset of each bucket in each block
	unsigned int* d_offsets;
	
	cudaMalloc((unsigned int**) &d_histo, histoBytes);
	cudaMalloc((unsigned int**) &d_offsets, histoBytes);
	
	//For each bit, starting with the LSB, perform the four kernels
	//Unsigned int is usually 16-bit in size
	//We have to keep track about parity of current step, to know where
	//is the sorted array now
	unsigned int iterations = 0;
	for (unsigned int i = 0; i < 8 * sizeof(unsigned int); i += b) 
	{
		cudaMemset(d_histo, 0, sizeof(unsigned int) * numBins); //zero out the bins
		cudaMemset(d_offset, 0, sizeof(unsigned int) * numBins); //zero out the bins		
		
		sort_blocks<<<numBlocks, elemsPerBlock, 2*elemsPerBlock*sizeof(unsigned int)>>>(d_in, d_out, d_inputPos, d_histo, d_offsets, numElems, i, b);
	
		//Perform in place scan on d_histo, obtaining global offsets for each bin
		scan(d_histo, histoSize);
		
		//Write to correct location
		write<<<numBlocks, elemsPerBlock>>>(d_in, d_out, d_histo, d_offsets, b, i, numBins);
		
		std::swap(d_in, d_out);
		iterations++;
	}
	
	//If iterated even number of times, correct positions are in d_inputVals
	if(iterations % 2 == 0)
	{
		cudaMemcpy(d_outputVals, d_inputVals, numElems*sizeof(unsigned int));
	}
	
	cudaFree(d_histo);
	cudaFree(d_offsets);
}
