#include "vez.h"

Vez::Vez(int N) {
	disky = new int[N];
	kapacita = N;
	vrch = -1;
	for(int i = 0; i < N; i++)
		disky[i] = 0;
};

bool Vez::prazdna() {
	return (vrch == -1);
}

bool Vez::plna() {
	return (vrch == kapacita-1);
}

int Vez::vyjmi() {
	if(prazdna()) return -1; 
	int ret = disky[vrch];
	disky[vrch--] = 0;
	return ret;
}

void Vez::vloz(int disk) {
	if(plna()) return;
	disky[++vrch] = disk;
}

int Vez::operator[](int i) {
	return disky[i];
}
