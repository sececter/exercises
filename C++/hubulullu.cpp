#include <iostream>

using namespace std;

int main() {
	int t, n, who;
	cin >> t;
	while(t--) {
		cin >> n;
		cin >> who;
		if(who == 0) cout << "Airborne wins." << endl;
		else cout << "Pagfloyd wins." << endl;
	}
	return 0;
}
