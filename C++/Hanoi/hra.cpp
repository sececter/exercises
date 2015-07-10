#include "hra.h"
#include <iostream>

using namespace std;

Hra::Hra(int N) {
	l = new Vez(N);
	s = new Vez(N);
	p = new Vez(N);
	this->N = N;
	stavy = new Stav[(1<<N)-1];
	vyres();
}

void Hra::presun(Vez *z, Vez *na, int krok) {
	int diskz = z->vyjmi();
	int diskna = na->vyjmi();
	
	if(diskz == -1) {
		z->vloz(diskna);
	}
	else if(diskna == -1) {
		na->vloz(diskz);
	}
	else if(diskz > diskna) {
		z->vloz(diskz);
		z->vloz(diskna);
	}
	else if(diskz < diskna) {
		na->vloz(diskna);
		na->vloz(diskz);
	}
	stavy[krok].l = l;
	stavy[krok].s = s;
	stavy[krok].p = p;
}

void Hra::vyres() {
	int kroku = (1<<N) - 1;
	for(int i = N; i >= 1; i--)
		l->vloz(i);
	for(int i = 0; i < kroku; i++) {
		if(i%3 == 0) presun(l, p, i);
		else if(i%3 == 1) presun(l, s, i);
		else if(i%3 == 2) presun(s, p, i);
		vykresli(i);
	}
}

void Hra::vykresli(int krok) {
	Vez* ll = stavy[krok].l;
	Vez* ls = stavy[krok].s;
	Vez* lp = stavy[krok].p;
	if(N%2 == 0) {
		Vez* temp = ls;
		ls = lp;
		lp = temp;
	}
	cout << "A : ";
	for(int i = 0; i < N; i++) {
		cout << (*ll)[i] << " ";
	}
	cout << endl;
	cout << "B : ";
	for(int i = 0; i < N; i++) {
		cout << (*ls)[i] << " ";
	}
	cout << endl;
	cout << "C : ";
	for(int i = 0; i < N; i++) {
		cout << (*lp)[i] << " ";
	}
	cout << endl << endl;
}
