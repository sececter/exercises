#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

typedef unsigned int T;

T min(T x, T y, T z) {
    return std::min(x, std::min(y, z));
}

T levenstein(string& a, string& b, T len_a, T len_b) {
	if(len_a == 0) return len_b;
	if(len_b == 0) return len_a;
	T add;
	a[len_a-1] == b[len_b-1] ? add = 0 : add = 1;
	return min(	levenstein(a, b, len_a-1, len_b) + 1,
					levenstein(a, b, len_a, len_b-1) + 1,
					levenstein(a, b, len_a-1, len_b-1) + add);
}
	

int main() {
	T test_cases;
	cin >> test_cases;
	while(test_cases--) {
		string a;
		string b;
		cin >> a >> b;
		cout << levenstein(a, b, a.length(), b.length()) << endl;
	}
	return 0;
}
