#include <iostream>
#include <stack>
#include <string>

using namespace std;

int main() {
	int c;
	string s;
	cin >> c;
	stack<char> stck;
	while(c--) {
		cin >> s;
		for(unsigned int i = 0; i < s.length(); i++) {
			if(isalpha(s[i])) cout << s[i];
			else if(s[i] != ')') { stck.push(s[i]); }
			else if(s[i] == ')'){
				char t = stck.top();
				stck.pop();
				while(t != '(') {
					cout << t;
					t = stck.top();
					stck.pop();
				}
			}
			if(s[i] == '\0') {
				while(!stck.empty()){
					cout << stck.top();
					stck.pop();
				}
			}
		}
		cout << endl;
	}
}
				
