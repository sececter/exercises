#include <iostream>

using namespace std;
int main() {
	unsigned long long n, out;
	unsigned int t;
	cin >> t;
	while(t--) {
		cin >> n;
		out = 0;
		out = (n*n*n + 3*n*n + 2*n)/6;
		n /= 2;
		out += (n*n*n - n)/6;
		
		cout << out << endl;
	}
}
