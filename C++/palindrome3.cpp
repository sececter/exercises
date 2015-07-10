#include <iostream>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

void increaseByOne(string& ar, size_t* s) {
	int i = *s - 1;
	while(i >= 0) {
		if(ar[i]<'9') { 
			stringstream st;
			st << (int)(ar[i] - '0')+1;
			ar[i] = st.str()[0];
			return; 
		}
		else ar[i--] = '0';
	}
	if(i == -1 && *s >= 1) {
		ar[0] = '1';
		ar[*s] = '0';
		*s = *s + 1;
	}
}

int main () {
	string chars;
	size_t cases, s, l, r, m;
	bool inc;
	cin >> cases;
	while(cases--) {
		s = 0;
		inc = true;
		cin >> chars;
		s = chars.length();
		increaseByOne(chars, &s);
		l = s/2 -1;
		if(s%2 == 0) { r = s/2; m = l+1; }
		else { r = s/2 + 1;  m=l+2; }
		while(l >= 0 && r <= s-1) {
			if((chars[l] > chars[r] && (chars[r] == '0' && chars[l] != '0')) || !inc) break;
			if(chars[l] < chars[r] && (chars[r] != '0' && chars[l] == '0')) {
				cout << "2" << endl;
				increaseByOne(chars, &m);
				break; 
			}
			if(chars[l] == chars[r]) {
				if(chars[m-1] == '9') {
					increaseByOne(chars, &m);
					break;
				}
				if((s%2 == 1 && inc) || (chars[l] == '9') || (chars[l] == '0')) {
					increaseByOne(chars, &m);
					inc = false;
				}
				l--; r++; 
			}
		}
		chars = chars.substr(0,m);
		cout << chars;
		reverse(chars.begin(), chars.end());
		if(s%2 != 0 || !inc) chars = chars.substr(1,m);
		cout << chars << endl;
	}	
	return 0;
}

