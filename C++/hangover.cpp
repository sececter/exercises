#include <iostream>

using namespace std;

int main() {
	float n, sum;
	int m;
	cin >> n;
	while(n != 0.0) {
		m = 2;
		sum = 0.0;
		while(sum < n) {
			sum += 1/(float)m;
			m++;
		}
		cout << m - 2 << " card(s)" << endl;
		cin >> n;
	}	
	return 0;
}


