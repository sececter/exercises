#include <iostream>
#include <stdlib.h>
#include <sys/time.h>
#include <cmath>
using namespace std;

int main(int argc, char *argv[])
{
	//init generator
	struct timeval theTV;
	struct timezone theTZ;
	gettimeofday(&theTV, &theTZ);
	srandom(theTV.tv_usec);
	
	//generate sample
	int N = *argv[1];
	double sample[N];
	for(int i = 0; i < N; i++)
		sample[i] = (double) random() / (double) RAND_MAX;
	
	//calculate mean
	double mean;
	for(int i = 0; i < N; i++)
		mean += sample[i];
	mean /= N;
	
	//calculate variance
	double var;
	for(int i = 0; i < N; i++)
		var += (sample[i] - mean)*(sample[i] - mean);
	var /= N;
		
	cout << var << endl;
	return 0;
}
