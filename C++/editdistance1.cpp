#include <iostream>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

typedef unsigned int T;
typedef pair<T,T> pair_t;

T min(T x, T y, T z) {
    return std::min(x, std::min(y, z));
}

T levenstein(string& a, string& b, T len_a, T len_b, map<pair_t, T> d) {
	map<pair_t, T>::iterator it = d.find(pair_t(len_a,len_b));
	if(it != d.end()) return it->second;
	if(len_a == 0) {
		d.insert(pair<pair_t,T>(pair_t(len_a,len_b),len_b));
		return len_b;
	}
	if(len_b == 0) {
		d.insert(pair<pair_t,T>(pair_t(len_a,len_b),len_a));
		return len_a;
	}
	T add;
	a[len_a-1] == b[len_b-1] ? add = 0 : add = 1;
	T ret = min(	levenstein(a, b, len_a-1, len_b, d) + 1,
					levenstein(a, b, len_a, len_b-1, d) + 1,
					levenstein(a, b, len_a-1, len_b-1, d) + add);
	d.insert(pair<pair_t, T>(pair_t(len_a,len_b),ret));
	return ret;
}
	

int main() {
	T test_cases;
	cin >> test_cases;
	while(test_cases--) {
		string a;
		string b;
		map<pair_t, T> d;
		cin >> a >> b;
		cout << levenstein(a, b, a.length(), b.length(), d) << endl;
	}
	return 0;
}

