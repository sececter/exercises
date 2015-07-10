#include <stdio.h>

using namespace std;

typedef unsigned int T;

const unsigned short MAX_TREATS = 1000;

T inline max(T x, T y) {
	if(x>y) return x;
	else return y;
}

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
		for(T i = 0; i < num_of_treats-d; i++) {
			if(d == 0) max_profit[i][i] = treats[i]*num_of_treats;
			else {
				max_profit[i][i+d] = max(	max_profit[i+1][i+d] + treats[i]*(num_of_treats-d),
											max_profit[i][i+d-1] + treats[i+d]*(num_of_treats-d));
			}
		}
	}

	printf("%u", max_profit[0][num_of_treats-1]);

	return 0;
}
