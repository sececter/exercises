#include <iostream>
#include <vector>
#include <limits>

using namespace std;

typedef int weight_t;
typedef int value_t;

struct coin {
	weight_t weight;
	value_t value;
};

coin make_coin(weight_t weight, value_t value) {
	coin ret;
	ret.weight = weight;
	ret.value = value;
	return ret;
}

template<typename T>
T cmin(T a, T b) {
	if(a < b) return a;
	else return b;
}

value_t find_minimal_value(weight_t coins_weight_left, unsigned int number_of_coins_left, vector<coin> coins) {
	if(coins_weight_left == 0) return 0;
	if(coins_weight_left < 0 || (coins_weight_left > 0 && number_of_coins_left == 0)) return numeric_limits<value_t>::max();
	value_t other_coin = find_minimal_value(coins_weight_left, number_of_coins_left-1, coins);
	value_t this_coin = find_minimal_value(coins_weight_left - coins[number_of_coins_left].weight, number_of_coins_left, coins);
	if(this_coin != numeric_limits<value_t>::max() && other_coin != numeric_limits<value_t>::max()) return cmin<value_t>(other_coin, this_coin + coins[number_of_coins_left].value);
	else if(this_coin == numeric_limits<value_t>::max() && other_coin != numeric_limits<value_t>::max()) return other_coin;
	else if(this_coin != numeric_limits<value_t>::max() && other_coin == numeric_limits<value_t>::max()) return this_coin;
	else return -1;
}

int main() {
	unsigned int test_cases;
	cin >> test_cases;
	while(test_cases--) {
		unsigned int number_of_coins, n = 0;
		weight_t empty_pig, full_pig, coin_weight, coins_weight = 0;
		value_t coin_value = 0;
		vector<coin> coins;
		vector<unsigned int> how_many_coins;
		cin >> empty_pig >> full_pig;
		coins_weight = full_pig - empty_pig;
		cin >> number_of_coins;
		n = number_of_coins;
		while(n--) {
			cin >> coin_value >> coin_weight;
			coins.push_back(make_coin(coin_weight, coin_value));
		}
		cout << find_minimal_value(coins_weight, number_of_coins-1, coins) << endl;
	}
	return 0;
}
