#include <iostream>
using namespace std;
int main() {
	unsigned short m,n;
	double long f;
	cin >> m;
	for(unsigned short i = 0; i < m; i++) {
		f = 1;
		cin >> n;
		while(n > 0) {
			f *= n;
			n--;
		}
		cout << f << endl;
	}	
	return 0;
}
