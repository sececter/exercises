#include <stdio.h>

using namespace std;

typedef unsigned short T;

int main() {
	T budget, parties;
	while(scanf("%hu %hu",&budget,&parties), budget != 0 && parties != 0) {
		T price[parties];
		T value[parties];
		T mv[budget];	//Max value for given budget
		T mp[budget];	//mp[i] is price to pay to reach mv[i]
		for(T i = 0; i < parties; i++)
			scanf("%hu %hu",&price[i],&value[i]);
		for(T i = 0; i <= budget; i++) {
			mv[i] = 0;
			mp[i] = 0;
		}
		for(T i = 1; i <= budget; i++) {
			T max_value = 0, max_price = 0;
			for(T j = 0; j < parties; j++) {
				if(i >= price[j] && (value[j] + mv[i - price[j]] > 0 || i == price[j])) {
					T current_value = value[j] + mv[i - price[j]];
					T current_price = price[j] + mp[i-price[j]];
					if(current_value > max_value) {
						max_value = current_value;
						max_price = current_price;
					} else if(current_value == max_value && current_price < max_price) {
						max_price = current_price;
					}
				}
			}
			mv[i] = max_value;
			mp[i] = max_price;
		}
		printf("%u %u", mp[budget],mv[budget]);
	}
	return 0;
}
