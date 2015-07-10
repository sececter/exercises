#include <iostream>
#include <list>

using namespace std;

int main() {
	int t, g, m, a, gmax, mmax;
	cin >> t;
	while(t--) {
		cin >> g;
		cin >> m;
		gmax = 0; mmax = 0;
		while(g--) {
			cin >> a;
			if(a > gmax) gmax = a;
		}
		while(m--) {
			cin >> a;
			if(a > mmax) mmax = a;
		}
		//cout << "gmax = " << gmax << ". mmax = " << mmax << endl;
		if(gmax >= mmax) cout << "Godzilla" << endl;
		else cout << "MechaGodzilla" << endl;
	}
	return 0;
}

