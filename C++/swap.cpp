#include <iostream>
using namespace std;
void swap(double &a, double &b)
{
	double c = a;
	a = b;
	b = c;
}

int main()
{
	double pi = 3.141592653589;
	double e = 2.7182818;
	cout	<< "Před prohozením: " << endl
			<< "pi = " << pi << ", e = " << e << endl;
	swap(pi, e);
	cout 	<< "Po prohozeni: " << endl
			<< "pi = " << pi << ", e = " << e << endl;
	return 0;
}
