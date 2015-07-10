#include <iomanip>
#include <iostream>
using namespace std;

const int N = 1000000000;			//Horni mez
const int M = 10;			//Pocet sloupcu

void sito (int *pole, int n)
{
	//Do pole se uloží celá čísla
	for(int *u = pole, i = 0; u < pole+n; u++)
		*u = i++;
		
	//Algoritmus sita
	*(pole+1) = 0;
	for(int *u = pole; u < pole+n; u++)
		//u dereferencujeme
		if(*u)
		{
			//u-pole je vzdálenost dalšího prvočísla (*u!=0) od začátku
			int dist = u - pole;
			for(int *v = u+dist; v < pole+n; v+= dist)
				*v = 0;
		}
}

void vypis(int *pole, int n, int o)
{
	int i = 1;
	cout << "Vypis prvocisel od " << o << " do " << N << endl;
	for(int u = o; u < n; u++)
		if(pole[u])
		{
			cout << setw(5) << pole[u];
			if (i++ % M == 0) cout << endl;
		}
}

int main()
{
	int A[N];
	sito(A, N);
	vypis(A, N, 1);
	return 0;
}
