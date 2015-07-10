#include <iostream>
#include <string>

using namespace std;

int possible;
string s;

//Takes account of all the tuples after the one on position "start" using
//recursion
void findNextPossible(size_t start) {
	if(start + 2 <= s.length()){
		string ss = s.substr(start, 2);
		if(ss <= "26") {
			possible++;
			for(size_t i = 0; i <= s.length(); i++) findNextPossible(start+2+i);
		}
	}
}

int main() {
	size_t pos, pos_t;
	bool test, someDeletedInTheMiddle;
	while(cin >> s, s.at(0) != '0') {
		possible = 0;
		test = true;
		someDeletedInTheMiddle = false;
		pos = s.find('0');
		//This just in effort to lower the number of find() calls
		pos_t = pos;
		//Tests if input is a valid code (30,40,... not allowed)
		while(pos_t != string::npos) {
			if(s.at(pos_t - 1) > '2') {
				test = false;
				break;
			}
			pos_t = s.find('0', pos_t+1);
		}
		if(test) {
			//Delete all tuples that could be read just one way
			//i.e. 10, 20
			while(pos != string::npos) {
				if((pos >= 2 && pos < s.length()-1) && s.length() > 2) someDeletedInTheMiddle = true;
				s.erase(s.find('0')-1, 2);
				pos = s.find('0');
			}
			if(!someDeletedInTheMiddle) possible++;
			for(size_t i = 0; i < s.length(); i++) {
				findNextPossible(i);
			}
		}		
		cout << possible << endl;
	}
	return 0;
}
