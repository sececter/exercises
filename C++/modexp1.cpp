# include <iostream>

using namespace std;

int main(void){
	int t, a, b, r, x;
	cin >> t;
	for(int w = 0; w < t; w++){
		cin >> a >> b;
		x = 1;
		while(b != 0) {
			r = b % 2;
			b /= 2;
			if(r == 1) x = (x*a) % 10;
			a = (a*a) % 10;
		}
		cout << x << endl;
	}
return 0;
} 
