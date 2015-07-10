#include <iostream>

using namespace std;

const int MAX_KAPACITA = 30;

class Vez {
public:
	Vez(int N);
	~Vez();
	int vyjmi();
	void vloz(int disk);
	int operator[](int i);
private:
	int vrch;
	int* disky;
	int kapacita;
	bool prazdna();
	bool plna();
};

struct Stav { Vez *l, *s, *p; };

class Hra {
public:
	Hra(int N);
	void vykresli(int krok);
private:
	int N;
	Vez *l, *s, *p;
	Stav* stavy;
	void presun(Vez *z, Vez *na, int krok);
	void vyres();
};

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

int main() {
	int N;
	cout << "Zadejte pocet disku: ";
	cin >> N;
	
	Hra h(N);
}

