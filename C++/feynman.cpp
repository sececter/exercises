#include <iostream>
using namespace std;
int main() {
	int n;
	cin >> n;
	while(n != 0){
		int s = 0;
		for(int i = 0; i < n; i++) {
			s += (i+1)*(i+1);
		}
		cout << s << endl;
		cin >> n;
	}
	return 0;	
}
