#include "utils.h"
#include <thrust/host_vector.h>
#include "reference_calc.cpp"

__global__
void computeMask(	const uchar4* const d_sourceImg, 
					unsigned char* d_mask, 
					const size_t sizeSource,
					const size_t numColsSource)
{
	int tid = blockDim.x * blockIdx.x + threadIdx.x;
	if(tid < sizeSource) 
	{
		bool isMask = (d_sourceImg[tid].x + d_sourceImg[tid].y + d_sourceImg[tid].z < 3 * 255) ? 1 : 0;
		d_mask[tid] = (char)isMask;
		__syncthreads();
		if(	isMask && 
			(d_mask[tid + numColsSource] == 0 || d_mask[tid - numColsSource] == 0 ||
			d_mask[tid + 1] == 0 || d_mask[tid - 1] == 0)) 
		{
			d_mask[tid] = 2;
		}
	}
}

__global__
void computeG(	const unsigned char* const d_channel,
				unsigned char* d_mask,
				float* d_g,
				const size_t sizeSource,
				const size_t numColsSource)
{
	int tid = blockDim.x * blockIdx.x + threadIdx.x;
	if(tid < sizeSource && d_mask[tid] == 1)
	{
		float sum = 4.f*d_channel[tid];
		
		sum -= (float)d_channel[tid + numColsSource] + (float)d_channel[tid - numColsSource];
		sum -= (float)d_channel[tid + 1] + (float)d_channel[tid - 1];
		
		d_g[tid] = sum;
	}
}

__global__
void jacobiIteration(	float* d_prev, 
						float* d_next, 
						unsigned char* d_mask, 
						unsigned char* d_sourceImg, 
						const unsigned char* const d_destImg,
						const size_t sizeSource,
						const size_t numColsSource)
{
	int tid = blockDim.x * blockIdx.x + threadIdx.x;
	if(tid < sizeSource && d_mask[tid] == 1)
	{
		float sum1 = 0.f;
		float sum2 = 4.f*d_sourceImg[tid]-d_sourceImg[tid + numColsSource]-d_sourceImg[tid - numColsSource]-d_sourceImg[tid + 1]-d_sourceImg[tid - 1];
		
		if(d_mask[tid + numColsSource] == 1)	sum1 += d_prev[tid + numColsSource];
		if(d_mask[tid + numColsSource] == 2)	sum1 += (float)d_destImg[tid + numColsSource];
		if(d_mask[tid - numColsSource] == 1)	sum1 += d_prev[tid - numColsSource];
		if(d_mask[tid - numColsSource] == 2)	sum1 += (float)d_destImg[tid - numColsSource];
		if(d_mask[tid + 1] == 1)				sum1 += d_prev[tid + 1];
		if(d_mask[tid + 1] == 2)				sum1 += (float)d_destImg[tid + 1];
		if(d_mask[tid - 1] == 1)				sum1 += d_prev[tid - 1];
		if(d_mask[tid - 1] == 2)				sum1 += (float)d_destImg[tid - 1];
		
		float next_val = (sum1 + sum2 ) / 4.f;
		d_next[tid] = min(255.f, max(0.f, next_val));	
	}
}

__global__
void splitIntoChannels(	const uchar4* const d_in,
						unsigned char* d_red,
						unsigned char* d_blue,
						unsigned char* d_green,
						const size_t sizeSource)
{
	int tid = blockDim.x * blockIdx.x + threadIdx.x;
	if(tid < sizeSource)
	{
		d_red[tid] = d_in[tid].x;
		d_blue[tid] = d_in[tid].y;
		d_green[tid] = d_in[tid].z;
	}
}

__global__
void copyChannels(	uchar4* d_blendedImage,
					float* d_red,
					float* d_blue,
					float* d_green,
					unsigned char* d_mask,
					const size_t sizeSource)
{
	int tid = blockDim.x * blockIdx.x + threadIdx.x;
	if(tid < sizeSource && d_mask[tid] == 1)
	{
		d_blendedImage[tid].x = d_red[tid];
		d_blendedImage[tid].y = d_blue[tid];
		d_blendedImage[tid].z = d_green[tid];
	}
}

__global__
void copySrcToBlended(	float* blended,
						unsigned char* src,
						const size_t sizeSource)
{
	int tid = blockDim.x * blockIdx.x + threadIdx.x;
	if(tid < sizeSource)
	{
		blended[tid] = (float)src[tid];
	}
}

void your_blend(const uchar4* const h_sourceImg,  //IN
                const size_t numRowsSource, const size_t numColsSource,
                const uchar4* const h_destImg, //IN
                uchar4* const h_blendedImg) //OUT
{
	const size_t sizeSource = numRowsSource * numColsSource;
	const size_t threadsPerBlock = 500;
	const size_t numBlocks = sizeSource / threadsPerBlock;
	const size_t numberOfIterations = 800;
	
	unsigned char* d_mask;
	uchar4* d_sourceImg;
	uchar4* d_destImg;
	unsigned char* d_red_src;
	unsigned char* d_blue_src;
	unsigned char* d_green_src;
	unsigned char* d_red_dst;
	unsigned char* d_blue_dst;
	unsigned char* d_green_dst;
	float* d_g_red;
	float* d_g_blue;
	float* d_g_green;
	float* d_blendedValsRed_1;
	float* d_blendedValsRed_2;
	float* d_blendedValsBlue_1;
	float* d_blendedValsBlue_2;
	float* d_blendedValsGreen_1;
	float* d_blendedValsGreen_2;
	uchar4* d_blendedImg;
	
	
	checkCudaErrors(cudaMalloc((unsigned char**) &d_mask, sizeSource*sizeof(unsigned char)));
	checkCudaErrors(cudaMalloc((uchar4**) &d_sourceImg, sizeSource*sizeof(uchar4)));
	checkCudaErrors(cudaMalloc((uchar4**) &d_destImg, sizeSource*sizeof(uchar4)));
	
	checkCudaErrors(cudaMalloc((unsigned char**) &d_red_src, sizeSource*sizeof(unsigned char)));
	checkCudaErrors(cudaMalloc((unsigned char**) &d_blue_src, sizeSource*sizeof(unsigned char)));
	checkCudaErrors(cudaMalloc((unsigned char**) &d_green_src, sizeSource*sizeof(unsigned char)));
	checkCudaErrors(cudaMalloc((unsigned char**) &d_red_dst, sizeSource*sizeof(unsigned char)));
	checkCudaErrors(cudaMalloc((unsigned char**) &d_blue_dst, sizeSource*sizeof(unsigned char)));
	checkCudaErrors(cudaMalloc((unsigned char**) &d_green_dst, sizeSource*sizeof(unsigned char)));
	
	checkCudaErrors(cudaMalloc((float**) &d_g_red, sizeSource*sizeof(float)));
	checkCudaErrors(cudaMalloc((float**) &d_g_blue, sizeSource*sizeof(float)));
	checkCudaErrors(cudaMalloc((float**) &d_g_green, sizeSource*sizeof(float)));
	
	checkCudaErrors(cudaMalloc((float**) &d_blendedValsRed_1, sizeSource*sizeof(float)));
	checkCudaErrors(cudaMalloc((float**) &d_blendedValsRed_2, sizeSource*sizeof(float)));
	checkCudaErrors(cudaMalloc((float**) &d_blendedValsBlue_1, sizeSource*sizeof(float)));
	checkCudaErrors(cudaMalloc((float**) &d_blendedValsBlue_2, sizeSource*sizeof(float)));
	checkCudaErrors(cudaMalloc((float**) &d_blendedValsGreen_1, sizeSource*sizeof(float)));
	checkCudaErrors(cudaMalloc((float**) &d_blendedValsGreen_2, sizeSource*sizeof(float)));
	
	checkCudaErrors(cudaMalloc((uchar4**) &d_blendedImg, sizeSource*sizeof(uchar4)));
	
	
	checkCudaErrors(cudaMemcpy((void *)d_sourceImg, (void *)h_sourceImg, sizeSource*sizeof(uchar4), cudaMemcpyHostToDevice));
	
	computeMask<<<numBlocks, threadsPerBlock>>>(d_sourceImg, d_mask, sizeSource, numColsSource);
	cudaDeviceSynchronize(); checkCudaErrors(cudaGetLastError());
	
	splitIntoChannels<<<numBlocks, threadsPerBlock>>>(d_sourceImg, d_red_src, d_blue_src, d_green_src, sizeSource);
	splitIntoChannels<<<numBlocks, threadsPerBlock>>>(d_destImg, d_red_dst, d_blue_dst, d_green_dst, sizeSource);
	cudaDeviceSynchronize(); checkCudaErrors(cudaGetLastError());
	
	checkCudaErrors(cudaMemset(d_g_red, 0, sizeSource*sizeof(float)));
	checkCudaErrors(cudaMemset(d_g_blue, 0, sizeSource*sizeof(float)));
	checkCudaErrors(cudaMemset(d_g_green, 0, sizeSource*sizeof(float)));
	computeG<<<numBlocks, threadsPerBlock>>>(d_red_src, d_mask, d_g_red, sizeSource, numColsSource);
	computeG<<<numBlocks, threadsPerBlock>>>(d_blue_src, d_mask, d_g_blue, sizeSource, numColsSource);
	computeG<<<numBlocks, threadsPerBlock>>>(d_green_src, d_mask, d_g_green, sizeSource, numColsSource);
	cudaDeviceSynchronize(); checkCudaErrors(cudaGetLastError());
	
	copySrcToBlended<<<numBlocks, threadsPerBlock>>>(d_blendedValsRed_1, d_red_src, sizeSource);
	copySrcToBlended<<<numBlocks, threadsPerBlock>>>(d_blendedValsRed_2, d_red_src, sizeSource);
	copySrcToBlended<<<numBlocks, threadsPerBlock>>>(d_blendedValsBlue_1, d_blue_src, sizeSource);
	copySrcToBlended<<<numBlocks, threadsPerBlock>>>(d_blendedValsBlue_2, d_blue_src, sizeSource);
	copySrcToBlended<<<numBlocks, threadsPerBlock>>>(d_blendedValsGreen_1, d_green_src, sizeSource);
	copySrcToBlended<<<numBlocks, threadsPerBlock>>>(d_blendedValsGreen_2, d_green_src, sizeSource);
	cudaDeviceSynchronize(); checkCudaErrors(cudaGetLastError());	
	
	for(size_t i = 0; i < numberOfIterations; i++)
	{
		jacobiIteration<<<numBlocks, threadsPerBlock>>>(d_blendedValsRed_1, d_blendedValsRed_2, d_mask, d_red_src, d_red_dst, sizeSource, numColsSource);
		std::swap(d_blendedValsRed_1,   d_blendedValsRed_2);
	}
	for(size_t i = 0; i < numberOfIterations; i++)
	{
		jacobiIteration<<<numBlocks, threadsPerBlock>>>(d_blendedValsBlue_1, d_blendedValsBlue_2, d_mask, d_blue_src, d_blue_dst, sizeSource, numColsSource);
		std::swap(d_blendedValsBlue_1,  d_blendedValsBlue_2); 
	}
	for(size_t i = 0; i < numberOfIterations; i++)
	{
		jacobiIteration<<<numBlocks, threadsPerBlock>>>(d_blendedValsGreen_1, d_blendedValsGreen_2, d_mask, d_green_src, d_green_dst, sizeSource, numColsSource);
		std::swap(d_blendedValsGreen_1, d_blendedValsGreen_2); 
	}
	cudaDeviceSynchronize(); checkCudaErrors(cudaGetLastError());
	
	checkCudaErrors(cudaMemcpy((void *)d_blendedImg, (void *)h_destImg, sizeSource*sizeof(uchar4), cudaMemcpyHostToDevice));
	
	copyChannels<<<numBlocks, threadsPerBlock>>>(d_blendedImg, d_blendedValsRed_1, d_blendedValsBlue_1, d_blendedValsGreen_1, d_mask, sizeSource);
	cudaDeviceSynchronize(); checkCudaErrors(cudaGetLastError());
	
	checkCudaErrors(cudaMemcpy(h_blendedImg, d_blendedImg, sizeSource*sizeof(uchar4), cudaMemcpyDeviceToHost));
}
