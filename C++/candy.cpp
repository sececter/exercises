#include <iostream>

using namespace std;
int main() {
	int N = 0;
	int n[10001];
	while(N != -1) {
		cin >> N;
		int sum = 0;
		for(int i = 0; i < N; i++) n[i] = 0;
		for(int i = 0; i < N; i++) {
			cin >> n[i];
			sum += n[i];
		}
		if(N > 0){
			if(N != 0 && sum%N == 0){
				int perone = sum/N;
				int moves = 0;
				for(int i = 0; i < N; i++) {
					if(n[i] > perone) moves += n[i]-perone;
				}
				cout << moves << endl;
			} else cout << -1 << endl;
		}
	}
	
	return 0;
}
		
