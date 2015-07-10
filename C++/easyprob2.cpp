#include <iostream>
#include <sstream>
#include <string>
#include <stack>

using namespace std;

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
	int power = bin.length()-1;
	if(power <= 0) cout << "0";
	for(size_t i = 0; i < bin.length(); i++) {
		if(bin[i] != '0') {
			cout << '2';
			if(power-i != 1) {
				cout << "(";
				binToBrack(decToBin(power-i));
				cout << ")";
			}
			cout << endl;
			cout << "power = " << power << endl;
			cout << "i = " << i << endl;
			cout << "bin.length() = " << bin.length() << endl;
			if(power-i != 0) cout << "+";
		}
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
	


