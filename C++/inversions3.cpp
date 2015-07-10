#include <iostream>

using namespace std;

long long int ar[300000];
long long int buff[300000];

long long int merge(int low, int middle, int high) {
	int i = low;
	int j = middle + 1;
	int k = low;
	long long int count = 0;
	
	for(int l = low; l <= high; l++) {
		buff[l] = ar[l];
	}
	
	while (i <= middle && j <= high) {
		if (buff[i] <= buff[j]) {
			ar[k] = buff[i];
			i++;
		} else {
			ar[k] = buff[j];
			j++;
			count += middle-i+1;
		}
			k++;
	}
	
	while (i <= middle) {
		ar[k] = buff[i];
		i++; k++;
	}
	while(j <= high) {
		ar[k] = buff[j];
		j++; k++; 
	}
	return count;
}

long long int invCount(int low, int high) {
	if(low < high) {
		int middle = low + (high - low)/2;
		
		return invCount(low, middle) + invCount(middle+1,high) + merge(low, middle, high);
	}
	return 0;
}

int main() {
	int t, n;
	cin >> t;
	while(t--) {
		cin >> n;
		for(int i = 0; i < n; i++) {
			cin >> ar[i];
		}
		cout << invCount(0,n-1) << endl;
	}
	return 0;
}
