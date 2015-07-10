#include <stdio.h>

using namespace std;

typedef unsigned int T;

const unsigned short MAX_PARTY = 200;
const unsigned short MAX_BUDGET = 600;

int main() {
	T budget, parties;
	while(scanf("%u %u",&budget,&parties), budget != 0 && parties != 0) {
		T price[parties];
		T fun[parties];
		T m[MAX_PARTY][MAX_BUDGET];	//m[i][j] maximum fun to get from all parties up to i with budget j
		T p[MAX_PARTY][MAX_BUDGET];	//p[i][j] minimum price to py to get max. fun from parties up to i with budget j
		
		price[0] = 0; fun[0] = 0;
		for(T i = 1; i <= parties; i++)
			scanf("%u %u",&price[i],&fun[i]);

		for(T i = 1; i <= parties; i++) {
			for(T j = 0; j <= budget; j++) {
				//We get more fun by attending party i
				if(price[i] <= j && m[i-1][j-price[i]] + fun[i] > m[i-1][j]) {
					m[i][j] = m[i-1][j-price[i]] + fun[i];
					p[i][j] = p[i-1][j-price[i]] + price[i];
				//We get same fun by attending i, but more cheaply
				} else if(price[i] <= j && m[i-1][j-price[i]] + fun[i] == m[i-1][j] && p[i-1][j-price[i]] + price[i] < p[i-1][j]) {
					m[i][j] = m[i-1][j-price[i]] + fun[i];
					p[i][j] = p[i-1][j-price[i]] + price[i];
				//We can't visit the party
				} else {
					m[i][j] = m[i-1][j];
					p[i][j] = p[i-1][j];
				}
			}
		}
			
		printf("%u %u\n", p[parties][budget], m[parties][budget]);
	}
	return 0;
}

