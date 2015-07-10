#include <stdio.h>
#include <algorithm>
#include <list>

using namespace std;

template<typename T>
int binarySearch(T* ar, int first, int last, T value) {
	int midPos = (first + last) / 2;
	while(ar[midPos] != value && first <= last) {
		if(ar[midPos] > value) last = midPos-1;
		else first = midPos+1;
		midPos = (first + last) / 2;
	}
	if(ar[midPos] != value) printf("Chyba v binsortu\n");
	return midPos;
}

int main() {
	int t, n, posB;
	long long int a[200000], b[200000], inversions;
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		inversions = 0;
		for(long long int i = 0; i < n; i++) {
			scanf("%lld", &a[i]);
			b[i] = a[i];
		}
		sort(b, b + n);
		for(long long int i = 0; i < n; i++) {
			posB = binarySearch<long long int>(b, 0, n-1, a[i]);
			inversions += posB - i;
		}
		printf("%lld\n", inversions);
	}
	return 0;
}
