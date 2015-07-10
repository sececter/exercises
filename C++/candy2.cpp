#include <iostream>

using namespace std;

int main() {
	long long int N,n,cases;
	cin >> cases;
	while(cases) {
		cin >> N;
		long int sum = 0;
		for(long int i = 0; i < N; i++) {
			cin >> n;
			sum += n%N;
		}
		if(N > 0){
			if(sum%N == 0) cout << "YES" << endl;
			else cout << "NO" << endl;
		} else {
			cout << "NO" << endl;
		}
		cases--;
	}
	
	return 0;
}
		
