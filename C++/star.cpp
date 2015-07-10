#include <iostream>
using namespace std;
int main() {
	int n;
	cout << "Enter any odd number: ";
	cin >> n;
	char arr[n];
	arr[n] = '\0';
	for(int i = 0; i < n; i++){ arr[i] = '-'; }
	for(int i = 0; i <= (n-1)/2; i++) {
		arr[i] = '*';
		arr[n-i-1] = '*';
		cout << arr << endl;
	}
	arr[(n-1)/2] = '-';
	cout << arr << endl;
	for(int i = 1; i < (n-1)/2; i++) {
		arr[((n-1)/2)-i] = '-';
		arr[((n-1)/2)+i] = '-';
		cout << arr << endl;
	}
	return 0;
}
