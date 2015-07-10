#include <iostream>
#include <string>
#include <map>

using namespace std;

string s;
map<int,int> m;

//Takes account of all the tuples after the one on position "start" using
//recursion
int findNextPossible(size_t start) {
	if(m.find(start) != m.end()) {
		return m.at(start);
	}
	int locWays;
	if(start + 2 <= s.length()){
		//Tuple considered
		string ss = s.substr(start, 2);
		//Otherwise not interpretable as a letter
		if(ss <= "26") {
			for(size_t i = 0; i <= s.length(); i++) locWays += findNextPossible(start+2+i);
			locWays++;
			m.insert(pair<int,int>(start, locWays));
		}
	}
	cout << locWays << endl;
	return locWays;
}

int main() {
	int ways;
	size_t pos;
	bool test, someDeletedInTheMiddle;
	//Until zero on input
	while(cin >> s, s.at(0) != '0') {
		ways = 0;
		test = true;
		someDeletedInTheMiddle = false;
		pos = s.find('0');
		//In this while I look for zeros
		while(pos != string::npos) {
			//Code with 30,40,... is not valid -> output 0
			if(s.at(pos - 1) > '2') {
				test = false;
				break;
			}
			//If delete some in the middle, output smaller by 1
			if((pos >= 2 && pos < s.length()-1) && s.length() > 2) someDeletedInTheMiddle = true;
			//Don't cosider the tuple with zero in it anymore
			s.erase(pos-1, 2);
			//Any other zero?
			pos = s.find('0', pos);
		}
		if(test) {
			if(!someDeletedInTheMiddle) ways++;
			//Process the rest
			for(size_t i = 0; i < s.length(); i++) {
				ways = findNextPossible(i);
			}
		}
		m.erase(m.begin(), m.end());
		cout << ways << endl;
	}
	return 0;
}

