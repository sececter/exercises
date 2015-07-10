#include <iomanip>
#include <iostream>
using namespace std;


void sito (unsigned int *pole, unsigned int n)
{
	//Do pole se uloží celá čísla
	for(unsigned int *u = pole, i = 0; u < pole+n; u++)
		*u = i++;
		
	//Algoritmus sita
	*(pole+1) = 0;
	for(unsigned int *u = pole; u < pole+n; u++)
		//u dereferencujeme
		if(*u)
		{
			//u-pole je vzdálenost dalšího prvočísla (*u!=0) od začátku
			int dist = u - pole;
			for(unsigned int *v = u+dist; v < pole+n; v+= dist)
				*v = 0;
		}
}

void vypis(unsigned int *pole, unsigned int n, unsigned int o)
{
	for(unsigned int u = o; u < n; u++)
		if(pole[u])
		{
			cout << pole[u] << endl;
		}
}

int main()
{
	unsigned short cases;
	unsigned int dolni;
	unsigned int horni;
	cin >> cases;
	for(unsigned int i = 0; i < cases; i++){
		cin >> dolni;
		cin >> horni;
		unsigned int* A = new unsigned int[horni];
		sito(A, horni);
		vypis(A, horni, dolni);
		delete[] A;
	}
	
	return 0;
}
