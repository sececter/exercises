#include "faktorial.h"

double faktorial(int n)
{
	double soucin = 1.0;
	int j = 1;
	while(j <= n)
	{
		soucin *= j++;
	}
	return soucin;
}
