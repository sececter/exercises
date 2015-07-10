#include <iostream>
#include <string>

using namespace std;

int main() {
	string sequence[8];
	sequence[0] = "TTT";
	sequence[1] = "TTH";
	sequence[2] = "THT";
	sequence[3] = "THH";
	sequence[4] = "HTT";
	sequence[5] = "HTH";
	sequence[6] = "HHT";
	sequence[7] = "HHH";
	unsigned short test_cases, occurences_found, test_case_in;
	string input;
	cin >> test_cases;
	for(int i = 1; i <= test_cases; i++) {
		cin >> test_case_in;
		cin >> input;
		cout << i;
		for(int j = 0; j < 8; j++) {
			occurences_found = 0;
			for(unsigned short k = 0; k < input.length(); k++) {
				if(input.substr(k,3) == sequence[j]) occurences_found++;
			}
			cout << " " << occurences_found;
		}
		cout << endl;
	}
	return 0;
}
