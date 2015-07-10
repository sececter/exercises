#include <stdio.h>
#include <cmath>

using namespace std;

typedef unsigned int T;

const unsigned short MAX_TREATS = 100;

int main() {
	unsigned short num_of_treats;
	T treats[MAX_TREATS];
	//max_profit[i][j] is the maximum profit gained from the subsequence of treats[] with
	//start i and end j
	T max_profit[MAX_TREATS][MAX_TREATS];

	//Input
	scanf("%hu", &num_of_treats);
	for(T i = 0; i < num_of_treats; i++)
		scanf("%u", &treats[i]);

	//Construct max_profit
	//max_profit[i][j] = max_profit with one of the edges removed, plus the value of the edge
	//times proper age
	for(T d = 0; d < num_of_treats; d++) {
		//Diagonal point
		max_profit[d][d] = treats[d]*num_of_treats;
		//Horizontal side
		for(T j = 1; j <= d; j++)
			max_profit[d][j] = max_profit[d][j-1] + treats[j]*(num_of_treats-abs(d-j));
		//Vertical side
		for(T i = 1; i <= d; i++)
			max_profit[i][d] = max_profit[i-1][d] + treats[i]*(num_of_treats-abs(d-i));
	}

	printf("%u", max_profit[0][num_of_treats-1]);

	return 0;
}
