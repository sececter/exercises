#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int atou(string& c) {
	int x = 0;
	for(size_t i = 0; i < c.length(); i++) x = x*10 + c[i] - '0';
	return x;
}

int main() {
	size_t t;
	long long int currentValue, currentNumber;
	string read, currentSign;
	cin >> t;
	while(t--) {
		currentValue = 0;
		currentNumber = 0;
		bool readDigit = true;
		currentSign.clear();
		cin >> read;
		while(read.find('=') == string::npos) {
			if(readDigit) {
				read.erase (std::remove (read.begin(), read.end(), ' '), read.end());
				currentNumber = atou(read);
				readDigit = false;
				if(!currentSign.empty()) {
					if(currentSign.find("+") != string::npos) currentValue += currentNumber;
					else if(currentSign.find("-") != string::npos) currentValue -= currentNumber;
					else if(currentSign.find("*") != string::npos) currentValue *= currentNumber;
					else if(currentSign.find("/") != string::npos) currentValue /= currentNumber;
					else if(currentSign.find("=") != string::npos) break;
					else break;
				} else {
					currentValue = currentNumber;
				}
			} else {
				currentSign = read;
				readDigit = true;
			}
			cin >> read;
		}
		cout << currentValue << endl;
	}
	return 0;
}
				
			
