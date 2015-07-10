#include <iostream>

using namespace std;

int main() {
	int t, n;
	long long int ar[300000], inversions;
	cin >> t;
	while(t--) {
		cin >> n;
		inversions = 0;
		for(long long int i = 0; i < n; i++) 
			cin >> ar[i];
		for(long long int i = 0; i < n; i++) 
			for(long long int j = i+1; j < n; j++) 
				if(ar[i] > ar[j]) inversions++;
		cout << inversions << endl;
	}
	return 0;
}
				
			
