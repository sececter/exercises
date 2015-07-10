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
		if(n%2 == 0) {
			out += (n*(n+2)*(2*n-1))/24;
		} else {
			out += ((n*n-1)*(2*n+3))/24;
		}
		cout << out << endl;
	}
}
