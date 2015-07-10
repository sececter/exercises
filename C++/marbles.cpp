#include <iostream>

using namespace std;

int main() {
	short test_cases;
	int n, k, i, j;
	long long int temp, result;
	cin >> test_cases;
	while(test_cases--) {
		cin >> n >> k;
		result = 1;
		for(i = 1; i <= k-1; i++) {
			result *= n+i;
			result /= i;
		}
		cout << "Partial result: " << result << endl;
		for(j = 2; j <= k-1; j++) {
			temp = 1;
			for(i = 1; i <= k-j; i++) {
				temp *= n+i;
				temp /= i;
			}
			result -= temp;
		}
		cout << result << endl;
	}
	return 0;
}
