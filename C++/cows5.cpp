#include <stdio.h>

using namespace std;

typedef unsigned int T;

const unsigned short MAX_TREATS = 2000;

T inline max(T x, T y) {
	if(x>y) return x;
	else return y;
}

int main() {
	unsigned short num_of_treats;
	T treats[MAX_TREATS];
	//max_profit[i][j] is the maximum profit gained from the subsequence of treats[] with
	//start i and end j
	T max_profit[2][MAX_TREATS];

	//Input
	scanf("%hu", &num_of_treats);
	for(T i = 0; i < num_of_treats; i++) {
		scanf("%u", &treats[i]);
		max_profit[1][i] = treats[i]*num_of_treats;
	}

	//Construct max_profit
	for(T d = 2; d <= num_of_treats; d++) 
		for(T i = 0; i < num_of_treats-d+1; i++)
			max_profit[d&1][i] = max(	max_profit[(d&1)^1][i] + treats[i+d-1]*(num_of_treats-d+1),
										max_profit[(d&1)^1][i+1] + treats[i]*(num_of_treats-d+1));

	printf("%u", max_profit[num_of_treats&1][0]);

	return 0;
}
