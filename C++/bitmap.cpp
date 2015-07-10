#include <stdio.h>
#include <vector>
#include <utility>

using namespace std;

typedef unsigned short T;

//Maximum size of the array
const size_t MAX = 200;

//Converts string to unsigned integer
T atou(char* s) {
	T x = 0;
	while(*s) x = x*10 + *(s++) - '0';
	return x;
}

//Calculates absolute value
T abs(int a) {
	if(a >= 0) return a;
	else return -a;
}

int main() {
	T testCases, n, m, i, j, min, curDist;
	T A[MAX][MAX];
	char row[MAX];
	//Storing coordinates (i,j) of ones and zeroes from the input matrix
	//hopefully saves a bit of time searching for closest ones
	vector< pair<T,T> > cOnes;
	vector< pair<T,T> > cZeroes;
	pair<T,T> nextPair;
	scanf("%hu",&testCases);
	while(testCases--) {
		//Input matrix is n X m
		scanf("%hu",&n);
		scanf("%hu",&m);
		//Starting from i=1, j=1 for clarity: dealing with i-th row, j-th column
		for(i = 1; i <= n; i++) {
			scanf("%s",row);
			for(j = 1; j <= m; j++) {
				//But then have to subtract one when dealing with char[]
				A[i][j] = atou(&row[j-1]);
				if(row[j-1] == '1') {
					cOnes.push_back(pair<T,T>(i,j));
					//Clearing the array for the next test case
					A[i][j] = 0;
				}
				else cZeroes.push_back(pair<T,T>(i,j));
			}
		}
		//For all zeroes find the closest one
		while(!cZeroes.empty()) {
			nextPair = cZeroes.back();
			i = nextPair.first;
			j = nextPair.second;
			cZeroes.pop_back();
			std::vector< pair<T,T> >::iterator it = cOnes.begin();
			min = abs(it->first - i) + abs(it->second - j);
			while(it != cOnes.end()) {
				curDist = abs(it->first - i) + abs(it->second - j);
				if(curDist < min) min = curDist;
				it++;
			}
			A[i][j] = min;
		}
		//Print the result
		for(i = 1; i <= n; i++) {
			for(j = 1; j <= m; j++) {
				printf("%hu ", A[i][j]);
				A[i][j] = 0;
			}
			printf("\n");
		}
	}
	return 0;
}
