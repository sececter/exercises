#include <iostream>

using namespace std;

int main() {
	int t, a, b, r;
	cin >> t;
	for(int w = 0; w < t; w++){
		cin >> a >> b;
		r = 1;
		for(int i = 0; i < b; i++) r = (r*a)%10;
		cout << r << endl;
	}
	return 0;
}
