#include <iostream>

using namespace std;

bool notInYet(int t[][1], int mi, int ma, int m) {
	bool val = true;
	for(int i = 0; i < m; i++)
		if(t[i][0] == mi && t[i][1] == ma)
			val = false;
	return val;
}

int main() {
	int n, m;
	int t[100000][1];
	cin >> n;
	m = 0;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j*i <= n && j <= i; j++) {
			if(notInYet(t, j, i, m)) {
				t[m][0] = j;
				t[m][1] = i;
				cout << "t[" << m << "] = (" << t[m][0] << ", " << t[m][1] << ")" << endl;
				m++;
			} 
		}
	}
	cout << m << endl;
	return 0;
}
