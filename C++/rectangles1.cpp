#include <iostream>
#include <cmath>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

int main() {
	int n;
	vector<pair<int,int> > s;
	cin >> n;
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j*i <= n && j <= i; j++) {
			if(!(find(s.begin(), s.end(), pair<int,int>(min(i,j), max(i,j))) != s.end())) {
				s.push_back(pair<int,int>(min(i,j), max(i,j)));
			} 
		}
	}
	cout << s.size() << endl;
	return 0;
}
