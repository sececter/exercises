#include <iostream>
#include <cmath>

using namespace std;

int main() {
	int n, sum;
	sum = 0;
	cin >> n;
	while(n) {
		for(int d = 1; d <= sqrt((double)n); d++)
			  if(n%d == 0) sum++;
		n--;
	}
	cout << sum << endl;
	return 0;
}
