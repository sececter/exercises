#include <iostream>
#include <cmath>

using namespace std;

int main() {
	double a, b, t;
	while(cin >> a >> b, a != -1 && b != -1) {
		if(b > a) {
			t = a;
			a = b;
			b = t;
		}
		cout << ceil(a/(b+1)) << endl;
	}
	return 0;
}
