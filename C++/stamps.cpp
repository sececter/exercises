#include <iostream>
#include <list>

using namespace std;

int main() {
	int t, i, friends, stamps, got, sum;
	cin >> t;
	for(int j = 1; j <= t; j++) {
		list<int> li;
		cin >> stamps;
		cin >> friends;
		cin >> got;
		li.push_front(got);
		friends--;
		while(friends--) {
			cin >> got;
			list<int>::iterator it=li.begin();
			for(; got < *it; it++);
			li.insert(it, got);
		}
		for(i = 0, sum = 0; 
			sum < stamps && !li.empty(); i++) {
			sum += li.front();
			li.pop_front();
		}
		cout << "Scenario #" << j << ":" <<  endl;
		if(sum < stamps) cout << "impossible" << endl;
		else cout << i << endl;
	}
	return 0;
}
