#include <iostream>
#include <string>

using namespace std;

typedef unsigned short T;

T min2(T x, T y) {
	if(x < y) return x;
	else return y;
}

T min3(T x, T y, T z) {
    return min2(x, min2(y, z));
}

int main() {
	T test_cases;
	cin >> test_cases;
	while(test_cases--) {
		string a;
		string b;
		cin >> a >> b;
		a.insert(0, " ");
		b.insert(0, " ");
		T d[a.length()][b.length()];
		for(unsigned short i = 0; i < a.length(); i++)
			for(unsigned short j = 0; j < b.length(); j++)
				d[i][j] = 0;
				
		for(unsigned short i = 1; i < a.length(); i++)
			d[i][0] = i;
			
		for(unsigned short j = 1; j < b.length(); j++)
			d[0][j] = j;
		
		for(unsigned short j = 1; j < b.length(); j++) {
			for(unsigned short i = 1; i < a.length(); i++) {
				if(a[i] == b[j]) d[i][j] = d[i-1][j-1];
				else {
					d[i][j] = min3(	d[i-1][j] + 1,
									d[i][j-1] + 1,
									d[i-1][j-1] + 1);
				}
			}
		}
		cout << d[a.length()-1][b.length()-1] << endl;
	}
	return 0;
}


