#include <stdio.h>

using namespace std;

int main() {
	int t, n;
	long long int ar[200000], inversions;
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		inversions = 0;
		for(long long int i = 0; i < n; i++) {
			scanf("%lld", &ar[i]);
		}
				
		printf("%lld", inversions);
	}
	return 0;
}
