#include <iostream>
#include <sstream>
#include <string>

using namespace std;

int atoi(const char* s) {
	int x = 0;
	while(*s) x = x*10 + *s++ - '0';
	return x; 
}

int main(){
	size_t t, pluspos, eqpos, mpos;
	int a, b, c;
	string s, as, bs, cs;
	cin >> t;
	t*=2;
	t++;
	while(t--) {
		getline(cin, s);
		pluspos = s.find(" + "); eqpos = s.find(" = "); mpos = s.find("machula");
		if(pluspos != string::npos && eqpos != string::npos && mpos != string::npos) {
			//cout << mpos << endl;
			if(mpos < pluspos) {
				//cout << "1" << endl;
				bs = s.substr(pluspos+3, eqpos-pluspos-3);
				cs = s.substr(eqpos+3);
				b = atoi(bs.c_str());
				c = atoi(cs.c_str());
				//cout << "b = " << b << ", c = " << c << endl;
				a = c - b;
			}
			else if(pluspos < mpos && mpos < eqpos) {
				//cout << "2" << endl;
				as = s.substr(0, pluspos);
				cs = s.substr(eqpos+3);
				//cout << "as = " << as << ", cs = " << cs << endl;
				a = atoi(as.c_str());
				c = atoi(cs.c_str());
				b = c - a;
			}
			else if(mpos > eqpos) {
				//cout << "3" << endl;
				as = s.substr(0, pluspos); 
				bs = s.substr(pluspos+3, eqpos-pluspos-3);
				//cout << "as = " << as << ", bs = " << bs << endl;
				a = atoi(as.c_str());
				b = atoi(bs.c_str());
				c = a + b;
			}
		cout << a << " + " << b << " = " << c << endl;
		}
	}
	return 0;
}

