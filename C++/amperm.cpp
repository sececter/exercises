#include <iostream>

using namespace std;

int main() {
	int n;
	int p1[100000];
	int p2[100000];
	bool amb;
	while(cin >> n, n != 0) {
		amb = true;
		for(int i = 1; i <= n; i++) {
			cin >> p1[i];
			p2[p1[i]] = i;
		}
		for(int i = 1; i <= n; i++) {
			if(p1[i] != p2[i]) amb = false; 
		}
		//for(int i = 1; i <= n; i++) {
			//cout << p1[i]; 
		//}
		//cout << endl;
		//for(int i = 1; i <= n; i++) {
			//cout << p2[i]; 
		//}
		//cout << endl;
		if(amb) {
			cout << "ambiguous" << endl;
		} else {
			cout << "not ambiguous" << endl;
		}
		for(int i = 0; i <= n; i++) {
			p1[i] = 0; p2[i] = 0;
		}
	}
	return 0;
}
		
