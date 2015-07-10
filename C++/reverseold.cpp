#include <iostream>
#include <string>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

void reverse(string& s) {
	for(unsigned short j = 0; j < s.length()/2; j++) {
			char c = s[s.length()-j-1];
			s[s.length()-j-1] = s[j];
			s[j] = c;
	}
}


void trim(string& s) {
	int i = 0;
	while(s[i] == '0') {
		i++;
	}
	s = s.substr(i);
}

int main() {
	int n;
	cin >> n;
	for(int i = 0; i < n; i++) {
		string s1, s2;
		cin >> s1 >> s2;
		reverse(s1);
		reverse(s2);
		ostringstream st;
		int is1 = atoi(s1.c_str());
		int is2 = atoi(s2.c_str());
		st << is1 + is2;
		string sum = st.str();
		reverse (sum);
		trim(sum);
		cout << sum << endl;
	}
	
	return 0;
}

