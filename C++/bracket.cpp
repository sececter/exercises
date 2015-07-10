#include <iostream>
#include <string>
using namespace std;
int main() {
	string str;
	cout << "Zapište výraz: " << endl;
	getline(cin, str);
	int nl = 0; int nr = 0;
	if(str.find('(') == string::npos || str.find(')') == string::npos) {
		cout << 0 << endl;
		return 0;
	} else {
		string sub = str.substr(0);
		while(sub.find('(') != string::npos) {
			string::size_type lpos = sub.find('(');
			sub = sub.substr(lpos+1);
			nl++;
		}
		sub = str.substr(0);
		while(sub.find(')') != string::npos) {
			string::size_type rpos = sub.find(')');
			sub = sub.substr(rpos+1);
			nr++;
		}
	}
	if(nl == nr) cout << 1 << endl;
	else cout << 0 << endl;
	return 0;
}
