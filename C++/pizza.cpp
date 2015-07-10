#include <iostream>
#include <string>

using namespace std;

typedef unsigned short T;

int main() {
	T number_of_friends;
	string input;
	T halves = 0;
	T three_quarters = 0;
	T one_quarters = 0;
	T pizzas = 0;
	cin >> number_of_friends;
	while(number_of_friends--) {
		cin >> input;
		if(input[0] == '1' && input[2] == '2') halves++;
		else if(input[0] == '3' && input[2] == '4') three_quarters++;
		else if(input[0] == '1' && input[2] == '4') one_quarters++;
	}
	//Whole pizzas
	while(halves > 1) {
		halves -= 2;
		pizzas++;
	}
	while(three_quarters > 0 && one_quarters > 0) {
		three_quarters--;
		one_quarters--;
		pizzas++;
	}
	while(one_quarters > 3) {
		one_quarters -= 4;
		pizzas++;
	}
	while(halves > 0 && one_quarters > 1) {
		halves--;
		one_quarters -= 2;
		pizzas++;
	}
	//Part pizzas
	//Ways to get 3/4: 1/2 + 1/4, 3*1/4, 3/4
	while(halves > 0 && one_quarters > 0) {
		halves--;
		one_quarters--;
		pizzas++;
	}
	while(one_quarters > 2) {
		one_quarters -= 3;
		pizzas++;
	}
	while(three_quarters > 0) {
		three_quarters--;
		pizzas++;
	}
	
	//Ways to get 1/2: 2*1/4, 1/2
	while(one_quarters > 1) {
		one_quarters -= 2;
		pizzas++;
	}
	while(halves > 0) {
		halves--;
		pizzas++;
	}
	
	//Ways to get 1/4: 1/4
	while(one_quarters > 0) {
		one_quarters--;
		pizzas++;
	}
	
	cout << pizzas+1 << endl;
	
	return 0;
}
	
