#include <iostream>
#include <string>
#include <string.h>
#include <sstream>
#include <ctype.h>

int ato(char *c) {
	int x = 0;
	while(*c) x = x*10 + *c++ - '0';
	return x;
}

using namespace std;

int main() {
	size_t t, numPosBegin, numPosEnd, signPos;
	long long int currentValue, currentNumber;
	char c[20000];
	string input, numberString;
	cin >> t;
	while(t--) {
		cin >> input;
		numPosBegin = 0;
		numPosEnd = 0;
		signPos = 0;
		while(!isdigit(input[numPosBegin])) numPosBegin++;
		numPosEnd = numPosBegin;
		while(isdigit(input[numPosEnd+1])) numPosEnd++;
		numberString = input.substr(numPosBegin, numPosEnd-numPosBegin+1);
		strcpy(c, numberString.c_str());
		currentNumber = ato(c);
		currentValue = currentNumber;
		numPosBegin++;
		while(signPos <= input.length() && numPosEnd <= input.length()) {
			while(!isdigit(input[numPosBegin])) numPosBegin++;
			numPosEnd = numPosBegin;
			while(isdigit(input[numPosEnd+1])) numPosEnd++;
			numberString = input.substr(numPosBegin, numPosEnd-numPosBegin+1);
			strcpy(c, numberString.c_str());
			currentNumber = ato(c);
			numPosBegin++;
			while(isalnum(input[signPos]) || isdigit(input[signPos]) ||
				isspace(input[signPos])) signPos++;
			switch(input[signPos]) {
				case '+':
					currentValue += currentNumber;
					break;
				case '-':
					currentValue -= currentNumber;
					break;
				case '*':
					currentValue *= currentNumber;
					break;
				case '/':
					currentValue /= currentNumber;
					break;
				case '=':
					goto out;
					break;
				default:
					break;
			}
		}
		out:
		cout << currentValue << endl;
	}
	return 0;
}
