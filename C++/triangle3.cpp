#include <iostream>

using namespace std;
int main() {
	unsigned long long n, out;
	unsigned int t;
	cin >> t;
	while(t--) {
		cin >> n;
		out = 0;
		out = (2*n*n*n + 9*n*n - 2*n)/8;
		cout << out << endl;
	}
}


