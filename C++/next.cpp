#include <iostream>

using namespace std;

int main() {
	while(true) {
		int a1,a2,a3,q;
		cin >> a1 >> a2 >> a3;
		if(a1 == 0 && a2 == 0 && a3 == 0) break;
		if(a2 != 0 && a1 != 0 && a3%a2 == 0 && a2%a1 == 0 && a3/a2 == a2/a1) {
			q = a3/a2;
			cout << "GP " << a3*q << endl;
		} else {
			q = a3 - a2;
			cout << "AP " << a3 + q << endl;
		}

	}
	return 0;
}
		
