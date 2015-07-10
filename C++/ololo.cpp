#include <stdio.h>
#include <set>

using namespace std;

int main() {
	unsigned int pyanis, x, in;
	scanf("%u", &pyanis);
	x = 0;
	while(pyanis--) {
		scanf("%u",&in);
		x ^= in;
	}
	printf("%u", x);
	return 0;
}
