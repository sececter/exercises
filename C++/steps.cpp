#include <iostream>
using namespace std;
int main(){
	int cases,x,y;
	cin >> cases;
	while(cases--){
		cin >> x >> y;
		if(x-y == 2 || x-y == 0) {
			if(x%2 == 0 && y%2 == 0) cout << x+y << endl;
			else cout << x+y-1 << endl;
		} else cout << "No Number" << endl;
	}
}
