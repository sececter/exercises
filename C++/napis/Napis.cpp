#include <iostream>
#include <cstring>
#include "Napis.h"
using namespace std;

Napis::Napis()
{
	strcpy(text, "Nazdar!");
}
Napis::Napis(char x[])
{
	if(x) strcpy(text, x);
}

Napis::~Napis() { }

void Napis::vypis()
{
	cout << text << endl;
}
