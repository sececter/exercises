#include <iostream>
#include <sstream>
#include <string>

using namespace std;

void increaseByOne(char* ar, int* s) {
	//cout << "s = " << *s << endl;
	int i = *s-1;
	while(i >= 0) {
		if(ar[i]<'9') { 
			stringstream st;
			st << (int)(ar[i] - '0')+1;
			ar[i] = st.str()[0];
			cout << "ar[" << i << "] = " << ar[i] << endl;
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

bool isPalindrome(char* ar, int s) {
	for(int i = 0; i < s/2; i++)
		if(ar[i] != ar[s-1-i]) {
			//cout << "ar[" << i << "] = " << ar[i] << ", ar[" << s - i << "] = " << ar[s-i] << endl; 
			return false;
		}
	return true;
}
	

int main() {
	char chars[1000000];
	int cases; int s = 0;
	cin >> cases;
	while(cases--) {
		s = 0;
		cin >> chars;
		for(; chars[s] != '\0'; s++);
		increaseByOne(chars, &s);
		//cout << s << endl;;
		while(!isPalindrome(chars, s)) increaseByOne(chars, &s);
		for(int i = 0; i <= s; i++) cout << chars[i];
		cout << endl;
		for(int i = 0; i <= s+2; i++) {
			chars[i] = 0;
		}
	}	
	return 0;
}

