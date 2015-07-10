#include <iostream>

using namespace std;

unsigned int findMax(unsigned long long int n) {
	unsigned long long int ret = 0;
	n%2 == 0 ? ret += n/2 : ret += findMax(
	if(n/2 + n/3 + n/4 > n) {
		return findMax(n/2) + findMax(n/3) + findMax(n/4);
	} else return n;
}

int main() {
	unsigned long long int n;
	while(cin >> n) cout << findMax(n) << endl;
	return 0;
}
