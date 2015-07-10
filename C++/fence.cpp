#include <cstdio>
#include <cmath>

using namespace std;

int main() {
	int n;
	while(scanf("%i",&n), n!=0) {
		printf("%4.2f\n", (n*n)/(2*M_PI));
	}
	return 0;
}

