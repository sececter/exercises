#include <iostream>

int main() {
	using namespace std;
	int n;
	int zeros = 0;
	cout << "Enter a number to compute faktorial of: ";
	cin >> n;

	for (int i = 5; i <= n; i *= 5) {
		zeros += n/i;
	}
	
	cout << "Number of zeros in decimal expression of " << n << "! is "
		<< zeros << "." << endl;
}
