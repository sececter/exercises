/* Muj druhy
 * program v C++
 */

#include <iostream>

using namespace std;
int cislo;

long faktorial(int n);

int main()
{
	cout << "Zadej cislo: ";
	cin >> cislo;
	if((cislo > 12) || (cislo < 0))	cout << "To nepujde.";
	else
		cout << "Faktorial z " << cislo << " je " << faktorial(cislo);
	return 0;
}

long faktorial(int n)
{
	long soucin = 1;
	int j = 1;
	while(j <= n)
	{
		soucin *= j++;
	}
	return soucin;
}
