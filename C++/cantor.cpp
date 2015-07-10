#include <iostream>
using namespace std;
int main(){
	size_t t;
	unsigned long long int a, b, n, i, m;
	cin >> t;
	while(t--) {
		cin >> n;
		i = 1; m = 1;
		while(m < n) {
			i++;
			m = (i*(i+1))/2;
		}
		if(i%2 == 0) {
			b = m - n + 1;
			a = n - m + i;
		} else {
			a = m - n + 1;
			b = n - m + i;
		}
		//cout << "m = " << m << ", n = " << n << ", i = " << i << endl;
		cout<<"TERM "<<n<<" IS "<<a<<"/"<<b<<endl;
	}
	return 0;
}
