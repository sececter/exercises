#include <iostream>

using namespace std;

int main() {
	int t;
	unsigned long long int n,i,c;
	cin >> t;
	while(t--) {
		cin >> n;
		i = 0;
		c = 1;
		while(i < n) {
			if((c*c*c)%1000 == 888) i++;
			c++;
		}
		cout << c << endl;
	}
	return 0;
}
