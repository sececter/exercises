#include <iostream>
#include <string>
#include <sstream>
#include <set>

using namespace std;

int main() {
	string input;
	unsigned int next_number = 0 , digit_square = 0, j = 0;
	set<unsigned int> appeared;
	set<unsigned int>::iterator it;
	cin >> input;
	while(next_number != 1) {
		next_number = 0;
		j++;
		for(unsigned short i = 0; i < input.length(); i++) {
			digit_square = input[i] - '0';
			digit_square *= digit_square;
			next_number += digit_square;
		}
		if(next_number == 1) {
			cout << j << endl;
			return 0;
		}
		it = appeared.find(next_number);
		if(it != appeared.end()) {
			cout << -1 << endl;
			return 0;
		}
		appeared.insert(next_number);
		//Make a next number into input
		stringstream ss;
		ss << next_number;
		input = ss.str();
	}
	return 0;
}
