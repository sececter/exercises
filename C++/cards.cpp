#include <iostream>

using namespace std;

int main() {
	long long int test_cases, n;
	cin >> test_cases;
	while(test_cases--) {
		cin >> n;
		cout << ((n*(3*n+1))/2)%1000007 << endl;
	}
	return 0;
}
