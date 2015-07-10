#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef unsigned int T;

int main() {
	T test_cases;
	cin >> test_cases;
	while(test_cases--) {
		T rows, columns;
		cin >> rows >> columns;
		vector<T> best_route_row(columns);
		vector<T> next_row(columns);
		
		//Best route to first row is first row
		for(T column = 0; column < columns; column++) {
			T current_value;
			cin >> current_value;
			best_route_row.push_back(current_value);
		}
		
		for(T row = 1; row < rows; row++) {
			//Read the next row
			for(T column = 0; column < columns; column++) {
				T current_value;
				cin >> current_value;
				//Comparing with best route to the previous row, find most
				//valuable route to the current square
				T max_new_value, possible_new_value = 0;
				for(int i = -1; i <= 1; i++) {
					if(column+i >= 0 && column+i < columns) {
						possible_new_value = best_route_row[column+i] + current_value;
						if(possible_new_value > max_new_value) max_new_value = possible_new_value;
					}
				}
				next_row[column] = max_new_value;
			}
			//Next row is the new best route
			next_row.swap(best_route_row);
		}
		cout << *max_element(best_route_row.begin(), best_route_row.end()) << endl;
	}
	return 0;
}
			
