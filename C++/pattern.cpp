#include <iostream>

using namespace std;

int main() {
	char s[10] = "----1----";
	cout << s << endl;
	for(int i = 1; i < 5; i++) {
		s[4-i] = char((i+1)+'0');
		s[4+i] = char((i+1)+'0');
		cout << s << endl;
	}
return 0;
}
