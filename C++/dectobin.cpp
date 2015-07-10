#include <cmath>
#include <iostream>
#include <stack>
#include <cstdlib>

int main(int argc, char** argv) {
	using namespace std;
	stack<int> binary;
	int digits = 0;
	int dec;
	cin >> dec;
	
	while(dec > 0) {
		binary.push(dec % 2);
		digits++;
		dec = dec / 2;
	}
	
	while(!binary.empty()) {
		cout << binary.top();
		binary.pop();
	}
	cout << endl;
	return 0;
}
