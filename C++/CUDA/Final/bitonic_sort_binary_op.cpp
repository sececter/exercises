#include <iostream>
#include "stdio.h"

using namespace std;

int main()
{
	const int n = 8;
	int* arr = new int[n];
	cout << "Enter " << n << " elements to sort: " << endl;
	for(unsigned int i = 0; i < n; i++)
		scanf("%d", arr+i);
	cout << "OK, sorting..." << endl;
	for (int k = 2; k <= n; k*=2)
    {
        for (int j = k>>1; j > 0; j>>=1)
        {
			for(int i = 0; i < n; i++)
			{
				int ixj = i^j;
				if(ixj>i)
				{
					if(((i&k) == 0 && arr[i] > arr[ixj]) || ((i&k) != 0 && arr[i] < arr[ixj])) 
					{
						float temp = arr[i];
						arr[i] = arr[ixj];
						arr[ixj] = temp;
					}
				}
			}
        }
    }
	cout << "Here is the result: " << endl;
	for(unsigned int i = 0; i < n; i++)
		printf("%d ", arr[i]);
	return 0;
}

