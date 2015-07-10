#include <iostream>

using namespace std;

int main() {
	long long int first, third, thirdLast, sum, n, t, d;
	cin >> t;
	while(t--) {
		cin >> third >> thirdLast >> sum;
		n = (2*sum)/(third + thirdLast);
		cout << n << endl;
		d = (thirdLast - third)/(n-5);
		first = third - 2*d;
		for(long long int i = 0; i < n; i++) {
			cout << first + i*d << " ";
		}
		cout << endl;
	}
	return 0;
}
