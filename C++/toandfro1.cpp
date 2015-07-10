#include <iostream>
#include <string>

using namespace std;
int main() {
	int cols,rows,i,j,p;
	bool add;
	cin >> cols;
	while(cols != 0) {
		string orig;
		cin >> orig;
		rows = orig.length()/cols;
		char fin[200];
		i = 0; j = 0; p = 0;
		add = true;
		while(orig[i] != '\0') {
			fin[j] = orig[i];
			if(p < cols-1) {
				add? j +=rows : j -= rows;
				p++;
			} else { 
				j++;
				add ? add = false : add = true;
				p = 0;
			}
			i++;
		}
		fin[j] = '\0';
		cout << fin << endl;
		for(int m = 0; m <= 200; m++) fin[m] = 0;
		cin >> cols;
	}
	return 0;
}

