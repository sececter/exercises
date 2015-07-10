#include <cstdlib>
#include <iostream>
#include "seznam.h"
using namespace std;

void chyba()
{
	cout << "Nedostatek pameti" << endl;
	exit(1);
}

seznam::seznam()
{
	hlava = new(nothrow) prvek(0);
	if(!hlava) chyba();
	else zarazka = hlava;
}

seznam::~seznam()
{
	vyprazdni();
	delete zarazka;
}

void seznam::vyprazdni()
{
	while(hlava != zarazka)
	{
		prvek* p = hlava;
		hlava = hlava->Dalsi();
		delete p;
	}
}

prvek* seznam::vlozNaKonec(int d)
{
	prvek* p = new(nothrow) prvek(0);
	if(p)
	{
		zarazka->UlozDalsi(p);
		zarazka->UlozHodnotu(d);
		zarazka = p;
	}
	return p;
}

prvek* seznam::najdi(int d, prvek* pred)
{
	pred = 0;
	zarazka -> UlozHodnotu(d);
	prvek *p = hlava;
	while(p->Hodnota() != d)
	{
		pred = p;
		p = p->Dalsi();
	}
	if(p == zarazka) return 0;
	else return p;
}

void seznam::vyjmi(int d)
{
	prvek *pred, *p;
	if((p = najdi(d, pred)))
	{
		if(pred)
			pred->UlozDalsi(p->Dalsi());
		else
			hlava = p->Dalsi();
		delete p;
	}
}
