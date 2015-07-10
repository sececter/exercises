#include <iostream>

using namespace std;

void increaseByOne(int* ar, int* s) {
	//cout << "s = " << *s << endl;
	int i = *s-1;
	while(i >= 0) {
		if(ar[i]<9) { 
			ar[i] = ar[i]+1;
			//cout << "ar[" << i << "] = " << ar[i] << endl;
			return; 
		}
		else ar[i--] = 0;
	}
	if(i == -1 && *s > 1) {
		ar[0] = 1;
		ar[++*s] = 0;
	}
}

bool isPalindrome(int* ar, int s) {
	for(int i = 0; i < s/2; i++)
		if(ar[i] != ar[s-1-i]) {
			//cout << "ar[" << i << "] = " << ar[i] << ", ar[" << s - i << "] = " << ar[s-i] << endl; 
			return false;
		}
	return true;
}
	

int main() {
	char chars[1000000];
	int ints[1000000];
	int cases; int s = 0;
	cin >> cases;
	while(cases--) {
		for(int i = 0; i <= s+2; i++) {
			chars[i] = 0; ints[i] = 0;
		}
		s = 0;
		cin >> chars;
		for(; chars[s] != '\0'; s++) ints[s] = chars[s] - '0';
		increaseByOne(ints, &s);
		//cout << s << endl;;
		while(!isPalindrome(ints, s)) increaseByOne(ints, &s);
		for(int i = 0; i < s; i++) cout << ints[i];
		cout << endl;
	}	
	return 0;
}
