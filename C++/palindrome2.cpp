#include <iostream>
#include <sstream>

using namespace std;

void increaseByOne(char* ar, size_t* s) {
	//cout << "s = " << *s << endl;
	int i = *s-1;
	while(i >= 0) {
		if(ar[i]<'9') { 
			stringstream st;
			st << (int)(ar[i] - '0')+1;
			ar[i] = st.str()[0];
			//cout << "ar[" << i << "] = " << ar[i] << endl;
			return; 
		}
		else ar[i--] = '0';
	}
	if(i == -1 && *s >= 1) {
		ar[0] = '1';
		ar[++*s] = '0';
		//ar[*s+1] = '\0';
	}
}

void reverse(char* s, size_t l) {
	for(unsigned short j = 0; j < l/2; j++) {
			char c = s[l-j-1];
			s[l-j-1] = s[j];
			s[j] = c;
	}
}

int main () {
	char chars[1000000];
	size_t cases, s, l, r, m;
	bool inc;
	cin >> cases;
	while(cases--) {
		s = 0;
		inc = true;
		cin >> chars;
		for(; chars[s] != '\0'; s++);
		l = s/2 -1;
		s%2 == 0 ? r = s/2 : r = s/2 + 1;
		s%2 == 0 ? m = l+1 : m=l+2;
		//cout << "s = " << s << ", l = " << l << ", r = " << r << endl;
		while(l >= 0 && r <= s-1) {
			if(chars[l] > chars[r]) break;
			if(chars[l] < chars[r]) {
				increaseByOne(chars, &m);
				break; 
			}
			if(chars[l] == chars[r]) {
				l--; r++; 
				if(s%2 == 1 && inc) {
					increaseByOne(chars, &m);
					inc = false;
				}
			}
		}
		size_t i;
		for(i = 0; i < m; i++) cout << chars[i];
		reverse(chars, m);
		s%2 == 0 ? i = 0 : i = 1;
		for(; i < m; i++) cout << chars[i];
		cout << endl;
		for(i = 0; i <= s+2; i++) {
			chars[i] = 0;
		}
	}	
	return 0;
}
