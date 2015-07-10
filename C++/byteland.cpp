#include <iostream>
#include <map>

using namespace std;

map<unsigned long long int, unsigned long long int> lt;

unsigned int findMax(unsigned long long int n) {
	map<unsigned long long int, unsigned long long int>::iterator f = lt.find(n);
	if(f != lt.end()) return f->second;
	if(n/2 + n/3 + n/4 > n) {
		unsigned long long int ret = findMax(n/2) + findMax(n/3) + findMax(n/4);
		lt.insert(pair<unsigned long long int, unsigned long long int>(n,ret));
		return ret;
	} else {
		lt.insert(pair<unsigned long long int, unsigned long long int>(n,n));
		return n;
	}
}

int main() {
	unsigned long long int n;
	while(cin >> n) cout << findMax(n) << endl;
	return 0;
}
