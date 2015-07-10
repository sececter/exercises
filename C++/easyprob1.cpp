#include <iostream>
#include <sstream>
#include <string>
#include <stack>

using namespace std;

void reverse(string& s) {
	for(unsigned short j = 0; j < s.length()/2; j++) {
			char c = s[s.length()-j-1];
			s[s.length()-j-1] = s[j];
			s[j] = c;
	}
}

string decToBin(int dec) {
	stack<int> binary;
	int digits = 0;
	stringstream ss;
	
	while(dec > 0) {
		binary.push(dec % 2);
		digits++;
		dec = dec / 2;
	}
	
	while(!binary.empty()) {
		ss << binary.top();
		binary.pop();
	}
	return ss.str();
}

void binToBrack(string bin) {
	int l = bin.length()-1;
	reverse(bin);
	if(l <= 0) {
		cout << "0";
		return;
	}
	while(l >= 0) {
		if(bin[l] != '0') {
			cout << "2";
			if(l != 1) {
				cout << "(";
				binToBrack(decToBin(l));
				cout << ")";
			}
			if(l != 0) cout << "+";
		}
		l--;
	}		
}

int main() {
	int n;
	while(cin >> n, n > 0) {
		binToBrack(decToBin(n));
		cout << endl;
	}
	return 0;
}
	

