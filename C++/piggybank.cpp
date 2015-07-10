#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef unsigned int weight_t;
typedef unsigned int value_t;

struct coin {
	weight_t weight;
	value_t value;
	double value_per_gram;
};

coin make_coin(weight_t weight, value_t value) {
	coin ret;
	ret.weight = weight;
	ret.value = value;
	ret.value_per_gram = (double)(value/weight);
	return ret;
}

bool compare_by_value_per_gram(const coin& coin1, const coin& coin2) {
	return coin1.value_per_gram < coin2.value_per_gram;
}

int main() {
	unsigned int test_cases;
	cin >> test_cases;
	while(test_cases--) {
		unsigned int number_of_coins = 0;
		weight_t empty_pig, full_pig, coins_weight, coin_weight, min_value = 0;
		value_t coin_value = 0;
		vector<coin> coins;
		vector<unsigned int> how_many_coins;
		cin >> empty_pig >> full_pig;
		coins_weight = full_pig - empty_pig;
		cin >> number_of_coins;

		while(number_of_coins--) {
			cin >> coin_value >> coin_weight;
			coins.push_back(make_coin(coin_weight, coin_value));
		}
		sort(coins.begin(), coins.end(), compare_by_value_per_gram);

		how_many_coins.resize(coins.size());
		for(unsigned int i = 0; i < coins.size() && coins_weight > 0; i++) {
			how_many_coins[i] = coins_weight/coins[i].weight;
			coins_weight %= coins[i].weight;
			min_value += coins[i].value * how_many_coins[i];
		}
		if(coins_weight == 0) cout << "The minimum amount of money in the piggy-bank is " << min_value << "." << endl;
		else cout << "This is impossible." << endl;
	}
	return 0;
}
