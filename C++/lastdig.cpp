#include <iostream>
#include <string>

using namespace std;

int main() {
	unsigned short t, r, last, x;
	string a;
	unsigned long long b;
	cin >> t;
	for(int w = 0; w < t; w++){
		cin >> a >> b;
		last = a[a.length()-1] - '0';
		x = 1;
		while(b != 0) {
			r = b % 2;
			b /= 2;
			if(r == 1) x = (x*last) % 10;
			last = (last*last) % 10;
		}
		cout << x << endl;
	}
	return 0;
}
