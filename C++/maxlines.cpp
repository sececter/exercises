#include <stdio.h>

using namespace std;

int main() {
	long long int test_cases,r;
	double max_of_s;
	scanf("%lli",&test_cases);
	for(int i = 1; i <= test_cases; i++) {
		scanf("%lli",&r);
		max_of_s = (double)(1+16*r*r)/4;
		printf("Case %d: %.2f\n",i,max_of_s);
	}
	return 0;
}
