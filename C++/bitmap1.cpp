#include <iostream>
#include <string>
#include <queue>

using namespace std;

const unsigned short MAX = 200;

typedef unsigned short coordinate;
typedef pair<coordinate,coordinate> coordinates;

//Converts char[] to unsigned int
coordinate atou(char* s) {
	coordinate x = 0;
	while(*s) x = x*10 + *(s++) - '0';
	return x;
}

//Returns array of immediate neighbours of pixel of coordinates c
coordinates* neighbours_of(coordinates c) {
	static coordinates neighbours[7];
	coordinate i = c.first;
	coordinate j = c.second;
	neighbours[0] = coordinates(i+1,j);
	neighbours[1] = coordinates(i,j+1);
	neighbours[2] = coordinates(i-1,j);
	neighbours[3] = coordinates(i,j-1);
	return neighbours;
}

int main() {
	
	unsigned short test_cases, wave_number, initial_wave_size;
	coordinate m, n, i, j;
	int A[MAX][MAX];
	coordinates* directions;
	string row;
	queue<coordinates> ones;
	queue<coordinates> wave;
	coordinates current_coordinates;
	bool found_some_zero;
	cin >> test_cases;
	
	while(test_cases--) {
		
		//Input
		cin >> n;
		cin >> m;
		for(i = 0; i < n; i++) {
			cin >> row;
			for(j = 0; j < m; j++) {
				if(row[j] == '1') {
					A[i][j] = -1;
					ones.push(coordinates(i,j));
				} else A[i][j] = 0;
			}
		}
		
		//Initilization
		wave = ones;
		wave_number = 1;
		found_some_zero = true;
		
		//Filling algorithm
		while(found_some_zero) {
			found_some_zero = false;
			initial_wave_size = wave.size();
			while(initial_wave_size--) {
				current_coordinates = wave.front();
				directions = neighbours_of(current_coordinates);
				//Try all directions
				for(int k = 0; k < 4; k++) {
					i = directions[k].first;
					j = directions[k].second;
					//If on screen and not yet visited
					if(i < n && j < m && A[i][j] == 0) {
						//Mark visited
						A[i][j] = wave_number;
						//(i,j) will be part the next wave
						wave.push(coordinates(i,j));
						found_some_zero = true;
					}
				}
				wave.pop();
			}
			wave_number++;
		}
		
		//-1 to 0
		while(!ones.empty()) {
			current_coordinates = ones.front();
			i = current_coordinates.first;
			j = current_coordinates.second;
			A[i][j] = 0;
			ones.pop();
		}
		
		//Output
		for(i = 0; i < n; i++) {
			for(j = 0; j < m; j++)
				cout << A[i][j] << " ";
			cout << endl;
		}
	}
	return 0;
}
