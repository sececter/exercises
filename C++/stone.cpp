#include <iostream>
#include <vector>
#include <limits>

using namespace std;

typedef unsigned int T;

T max(T x, T y, T z) {
	if(x < y) {
		if(y < z) return z;
		else return y;
	}
	else {
		if(y > z) return x;
		else {
			if(x > z) return x;
			else return z;
		}
	}
}
		

T max_stones_found_following(T x, T y, vector< vector<T> > A) {
	if(y == A.size()-1) return A[x][y];
	else {
		T went_left, went_right, went_down;
		if(x-1 >= 0) went_left = max_stones_found_following(x-1, y+1, A);
		else went_left = numeric_limits<T>::min();
		if(x+1 <= A[x].size()-1) went_right = max_stones_found_following(x+1, y+1, A);
		else went_right = numeric_limits<T>::min();
		went_down = max_stones_found_following(x, y+1, A);
		return A[x][y] + max(went_left, went_right, went_down);
	}
}

int main() {
	T test_cases, rows, columns, stones_found, max_stones;
	vector< vector<T> > A;
	while(test_cases--) {
		cin >> rows >> columns;
		for(unsigned int i = 0; i < rows; i++) 
			for(unsigned int j = 0; j < columns; j++) 
				cin >> A[i][j];
		max_stones = 0;
		stones_found = 0;
		for(unsigned int j = 0; j < columns; j++) {
			stones_found = max_stones_found_following(0, j, A);
			if(stones_found > max_stones) max_stones = stones_found;
		}
		cout << max_stones << endl;
	}
	return 0;
}
