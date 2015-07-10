#include <iostream>
#include <sstream>
#include <string>
using namespace std;
int main() {
	cout << "Enter 1 - 20 integers to calculate averages from, " <<
		"separated by spaces: ";
	string raw;
	stringstream sts;
	getline(cin, raw);
	
	double arr[20];
	int i = 0;
	int j = 0;
	
	while(true) {
		while(raw[i] != ' ' && raw[i] != '\0'){
			sts << raw[i++];
		}
		arr[j++] = stod(sts.str());
		sts.str("");
		sts.clear();
		if(raw[i] == '\0') break;
		else i++;
	}
	
	double pavg = 0; double navg = 0; double avg = 0;
	int p = 0; int n = 0;
	for(int i = 0; i < j; i++) {
		if(arr[i] >= 0) {
			pavg += arr[i];
			p++;
		}
		else {
			navg += arr[i];
			n++;
		}
	}
	pavg /= p; navg /= n; avg = (pavg + navg)/(p+n);
	
	cout << "Average of positive numbers is: " << pavg << endl;
	cout << "Average of negative numbers is: " << navg << endl;
	cout << "Average is: " << avg << endl;
	
	return 0;
}
