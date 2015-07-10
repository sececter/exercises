#include "seznam.cpp"
int main()
{
	prvek *p;
	seznam S;
	for(int i = 0; i < 5; i++)
		if(!(S.vlozNaKonec(i))) chyba();
	cout << ((S.najdi(3,p)) ? "Je tam" : "neni") << endl;
	
	S.vyjmi(2);
}
