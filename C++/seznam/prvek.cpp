#include "prvek.h"
prvek::prvek(int d)
: data(d), dalsi(0)
{ }

void prvek::UlozHodnotu(int d)
{
	data = d;
}

int prvek::Hodnota()
{
	return data;
}

void prvek::UlozDalsi(prvek* p)
{
	dalsi = p;
}
prvek* prvek::Dalsi()
{
	return dalsi;
}
