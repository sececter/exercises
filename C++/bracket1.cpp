#include <iostream>
#include <string>

using namespace std;

int main() {
	string str;
	cout << "Zapište výraz: " << endl;
	getline(cin, str);
	if(str.find('(') == string::npos || str.find(')') == string::npos) {
		cout << 0 << endl;
		return 0;
	}
	int nl = 1; int nr = 1;
	string::size_type lpos = str.find('(');
	string::size_type rpos = str.find(')');
	if(lpos < rpos) {
		while(str.find('(', lpos+1) != string::npos || str.find(')', rpos+1) != string::npos) {
			if(str.find('(', lpos+1) != string::npos) {
				lpos = str.find('(', lpos+1);
				nl++;
			}
			if(str.find(')', rpos+1) != string::npos) {
				rpos = str.find(')', rpos+1);
				nr++;
			}
		}
	} else {
		cout << 0 << endl;
		return 0;
	}
	if(nl == nr) cout << 1 << endl;
	else cout << 0 << endl;
	return 0;
}
