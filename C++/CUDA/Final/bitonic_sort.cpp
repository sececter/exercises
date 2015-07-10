#include <iostream>
#include "stdio.h"

using namespace std;

void merge_up(int *arr, int n)
{
	int step = n/2;
	int temp;
	while(step > 0)
	{
		for(int i = 0; i < n; i += step*2)
		{
			for(int j = i, k = 0; k < step; j++, k++) 
			{
				if(arr[j] > arr[j+step])
				{
					temp = arr[j];
					arr[j] = arr[j+step];
					arr[j+step] = temp;
				}
			}
		}
		step /= 2;
	}
}

void merge_down(int *arr, int n)
{
	int step = n/2;
	int temp;
	while(step > 0)
	{
		for(int i = 0; i < n; i += step*2)
		{
			for(int j = i, k = 0; k < step; j++, k++) 
			{
				if(arr[j] < arr[j+step])
				{
					temp = arr[j];
					arr[j] = arr[j+step];
					arr[j+step] = temp;
				}
			}
		}
		step /= 2;
	}
}

int main()
{
	const unsigned int n = 8;
	int* arr = new int[n];
	cout << "Enter " << n << " elements to sort: " << endl;
	for(unsigned int i = 0; i < n; i++)
		scanf("%d", arr+i);
	cout << "OK, sorting..." << endl;
	for(unsigned int s = 2; s <= n; s *= 2)
		for(unsigned int i = 0; i < n; i += s*2)
		{
			merge_up((arr + i), s);
			merge_down((arr + i + s),s);
		}
	cout << "Here is the result: " << endl;
	for(unsigned int i = 0; i < n; i++)
		printf("%d ", arr[i]);
	return 0;
}
