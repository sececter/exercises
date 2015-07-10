#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

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
	return ret;
}

bool compare_by_weight(const coin& coin1, const coin& coin2) {
	return coin1.weight < coin2.weight;
}

int main() {
	unsigned int test_cases;
	cin >> test_cases;
	while(test_cases--) {
		//Initialization
		unsigned int number_of_coins, n = 0;
		weight_t empty_pig, full_pig, coin_weight, coins_weight;
		value_t coin_value, min_value, current_value = 0;
		vector<coin> coins;
		vector<unsigned int> min_value_for_the_weight;

		//Input
		cin >> empty_pig >> full_pig;
		cin >> number_of_coins;
		n = number_of_coins;
		while(n--) {
			cin >> coin_value >> coin_weight;
			coins.push_back(make_coin(coin_weight, coin_value));
		}

		//Input processing
		coins_weight = full_pig - empty_pig;
		sort(coins.begin(), coins.end(), compare_by_weight);
		min_value_for_the_weight.resize(coins_weight);
		for(unsigned int i = 0; i < coins_weight; i++) min_value_for_the_weight[i] = 0;

		//For all weights
		for(unsigned int i = 1; i <= coins_weight; i++) {
			//Find the smallest value
			min_value = numeric_limits<value_t>::max();
			for(unsigned int j = 0; j < number_of_coins; j++) {
				if(coins[j].weight <= i && (min_value_for_the_weight[i - coins[j].weight] > 0 || i == coins[j].weight)){
					current_value = coins[j].value + min_value_for_the_weight[i - coins[j].weight];
					if(current_value < min_value && current_value != 0) min_value = current_value;
				} else break;
			}
			if(min_value == numeric_limits<value_t>::max()) min_value = 0;
			min_value_for_the_weight[i] = min_value;
		}

		if(!min_value_for_the_weight[coins_weight])
			cout << "This is impossible." << endl;
		else
			cout << "The minimum amount of money in the piggy-bank is " << min_value_for_the_weight[coins_weight] << "." << endl;
		}
	return 0;
}
