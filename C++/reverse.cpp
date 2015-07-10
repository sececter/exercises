#include <iostream>
#include <string>

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
		string sum = to_string(stoi(s1) + stoi(s2));
		reverse (sum);
		trim(sum);
		cout << sum << endl;
	}
	
	return 0;
}
