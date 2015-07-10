#include <iostream>

using namespace std;

int main() {
	int t;
	unsigned long long int n;
	cin >> t;
	while(t--) {
		cin >> n;
		if(n > 0) {
			if(n%2 == 1) cout << 1 + ((n-1)*5)/2 << 92 << endl;
			else cout << 4 + ((n-2)*5)/2 << 42 << endl;
		} else cout << 0 << endl;	
	}
	return 0;
}

