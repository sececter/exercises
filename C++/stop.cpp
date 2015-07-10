#include <iostream>
#include <cmath>

using namespace std;

inline int isPowerOfTwo (unsigned long long int x)
{
  return ((x != 0) && ((x & (~x + 1)) == x));
}

int main() {
	unsigned long long int n;
	cin >> n;
	if(isPowerOfTwo(n)) cout << "TAK" << endl;
	else cout << "NIE" << endl;
	return 0;
}
