#include <iostream>

using namespace std;

int main() {
	int a[200];
	int cases,m,n,x,temp;
	cin >> cases;
	
	while(cases--) {
		cin >> n;
		temp = 0;
		m = 1;
		a[0] = 1;
		for(int i = 1; i <= n; i++) {
			for(int j = 0; j < m; j++) {
				x = a[j]*i + temp;
				a[j] = x%10;
				temp = x/10;
			}
			while(temp > 0) {
				a[m] = temp%10;
				temp /= 10;
				m++;
			}		
		}
		for(int i = m-1; i >= 0; i--){
		cout << a[i];
	}
	cout << endl;	
	}
return 0;	
}
