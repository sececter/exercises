#include <iostream>

using namespace std;

long long int binomial(int N, int K) {
  if( K > N - K )
    K = N - K;
  long long int c = 1;
  for(int i = 0; i < K; ++i) {
    c *= (N - i);
    c /= (i + 1);
  }
  return c;
}

int main() {
	short test_cases;
	int n, k;
	cin >> test_cases;
	while(test_cases--) {
		cin >> n >> k;
		cout << binomial(n-1,n-k) << endl;
	}
	return 0;
}
