#include <iostream>
#include <algorithm>

using namespace std;

int main() {
	int cases,N,sum;
	cin >> cases;
	while(cases--) {
		cin >> N;
		sum = 0;
		int* a = new int[N];
		int* b = new int[N];
		for(int i = 0; i < N; i++) {
			cin >> a[i];
		}
		for(int i = 0; i < N; i++) {
			cin >> b[i];
		}

		sort(a, a+N);
		sort(b, b+N);
		
		for(int i = 0; i < N; i++) {
			sum += (a[i])*(b[i]);
		}
		cout << sum << endl;
		delete[] a;
		delete[] b;
	}
	return 0;
}

