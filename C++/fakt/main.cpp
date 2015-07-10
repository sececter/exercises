#include <iostream>
#include "faktorial.cpp"
using namespace std;
const int DolniMez = 0, HorniMez = 50;
int cislo;

int main()
{
	cout << "Zadej cislo: ";
	cin >> cislo;
	if((cislo > HorniMez) || (cislo < DolniMez))	cout << "To nepujde.";
	else
		cout << "Faktorial z " << cislo << " je " << faktorial(cislo);
	return 0;
}
