#include <iostream>

using namespace std;
int main() {
	
	
	bool val;
	
	for(int i = 0; i < 12; i++) {
		char* a = new char[10];
		char* b = new char[5];
		cin >> a >> b;
		
		char* pa = a;
		char* pb = b;
		
		for(int j = 0; j < 5; j++) {
			*pa = a[j]; *pb = b[0];
			val = true;
			for(int k = 0; k < 5; k++) {
				if(pa[j+k] == b[k]) continue;
				else val = false;
			}
			if(val == true) break;
		}
		cout << val << endl;
		delete[] a;
		delete[] b;
	}
	return 0;
}
