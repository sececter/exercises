#include <iostream>
#include <string>
using namespace std;
int main() {
	int cols,rows;
	cin >> cols;
	while(cols != 0) {
		string orig;
		cin >> orig;
		rows = orig.length()/cols;
		char fin[cols*rows];
		int k = 0;
		for(int i = 0; i < rows; i++) {
			for(int j = 0; j < cols; j++) {
				if(i%2 == 0) fin[j*rows+i] = orig[k];
				else fin[j*rows+i] = orig[k];
				cout << j*rows+i << " ";
			}
		}
		cout << fin << endl;
		cin >> cols;
	}
	return 0;
}
