#include <iostream>
#include <cmath>

using namespace std;

class prvek {
public:
	prvek();
	prvek(int d, prvek* pred, prvek* dal);
	~prvek();
	int get_data();
	void set_data(int d);
	prvek* get_dalsi();
	void set_dalsi(prvek* p);
	prvek* get_predchozi();
	void set_predchozi(prvek* p);
		
private:
	int data;
	prvek* predchozi;
	prvek* dalsi;
};

class seznam {
public:
	seznam();
	~seznam();
	void vloz_konec(int d);
	void vloz_zacatek(int d);
	bool vloz_za(int za, int d);
	prvek* najdi(int d);
	prvek* smaz(int d);
	int vyjmi_prvni();
	int vyjmi_posledni();
	bool prazdny();
	void vypsat();
	void vymaz();

private:
	prvek* hlava;
	prvek* ocas;
};

prvek::prvek()
	: data(0), predchozi(NULL), dalsi(NULL)
{}

prvek::prvek(int d, prvek* pred, prvek* dal) 
	: data(d), predchozi(pred), dalsi(dal)
{}

prvek::~prvek() 
{}

int prvek::get_data() {
	return data;
}

void prvek::set_data(int d) {
	data = d;
}

prvek* prvek::get_dalsi() {
	return dalsi;
}

void prvek::set_dalsi(prvek* p) {
	dalsi = p;
}

prvek* prvek::get_predchozi() {
	return predchozi;
}

void prvek::set_predchozi(prvek* p) {
	predchozi = p;
}


seznam::seznam() {
	hlava = NULL;
	ocas = NULL;
}

seznam::~seznam() {
	vymaz();
}

void seznam::vloz_konec(int d) {
	if(ocas == NULL) {
		prvek* p = new prvek(d, NULL, NULL);
		hlava = p;
		ocas = p;
	} else {
		prvek* p = new prvek(d, ocas, NULL);
		ocas->set_dalsi(p);
		ocas = p;
	}
}

void seznam::vloz_zacatek(int d) {
	if(hlava == NULL) {
		prvek* p = new prvek(d, NULL, NULL);
		hlava = p;
		ocas = p;
	} else {
		prvek* p = new prvek(d, NULL, hlava);
		hlava->set_predchozi(p);
		hlava = p;
	}
}

bool seznam::vloz_za(int za, int d) {
	prvek* p = najdi(za);
	if(p != NULL) {
		prvek* orig_dalsi = p->get_dalsi();
		prvek* pr = new prvek(d, p, p->get_dalsi());
		p->set_dalsi(pr);
		orig_dalsi->set_predchozi(pr);
		return true;
	}
	return false;
}

prvek* seznam::najdi(int d) {
	prvek* p = hlava;
	while(p != NULL) {
		if(p->get_data() == d) break;
		p = p->get_dalsi();
	}
	return p;
}

prvek* seznam::smaz(int d) {
	prvek* p;
	if((p = najdi(d))) {
		if(p == hlava) {
			hlava = p->get_dalsi();
			hlava->set_predchozi(NULL);
		}
		else if(p == ocas) {
			ocas = p->get_predchozi();
			ocas->set_dalsi(NULL);
		} else {
			prvek* pred = p->get_predchozi();
			prvek* dal = p->get_dalsi();
			pred->set_dalsi(dal);
			dal->set_predchozi(pred);
		}
		delete p;
	} else p = NULL;
	return p;
}

int seznam::vyjmi_prvni() {
	prvek* p = hlava;
	int ret = p->get_data();
	hlava = hlava->get_dalsi();
	hlava->set_predchozi(NULL);
	delete p;
	return ret;
}

int seznam::vyjmi_posledni() {
	prvek* p = ocas;
	int ret = p->get_data();
	ocas = ocas->get_predchozi();
	ocas->set_dalsi(NULL);
	delete p;
	return ret;
}

bool seznam::prazdny() {
	return ocas == hlava;
}

void seznam::vypsat() {
	prvek* p = hlava;
	while(p != NULL) {
		cout << p->get_data() << endl;
		p = p->get_dalsi();
	}
}

void seznam::vymaz() {
	while(hlava != NULL) {
		prvek* p = hlava;
		hlava = hlava->get_dalsi();
		delete p;
	}
}

int main() {
	seznam* s = new seznam();
	cout << "1. Pridat hodnotu na zacatek seznamu" << endl;
	cout << "2. Pridat hodnotu na konec seznamu" << endl;
	cout << "3. Vyjmout hodnotu ze zacatku seznamu" << endl;
	cout << "4. Vyjmout hodnotu z konce seznamu" << endl;
	cout << "5. Odstranit zadanou hodnotu ze seznamu" << endl;
	cout << "6. Pridat za prvek" << endl;
	cout << "7. Vypsat seznam" << endl;
	cout << "8. Vyprazdnit seznam" << endl;
	cout << "x. Konec" << endl;
	while(true) {
		int volba, hodnota, za;
		cout << "Volba: ";
		cin >> volba;
		switch(volba) {
			case 1:
				cout << "Hodnota: ";
				cin >> hodnota;
				s->vloz_zacatek(hodnota);
			break;
			case 2: 
				cout << "Hodnota: ";
				cin >> hodnota;
				s->vloz_konec(hodnota);
			break;
			case 3:
				cout << s->vyjmi_prvni() << endl;
			break;
			case 4:
				cout << s->vyjmi_posledni() << endl;
			break;
			case 5:
				cout << "Hodnota: ";
				cin >> hodnota;
				s->smaz(hodnota);
			break;
			case 6:
				cout << "Za: ";
				cin >> za;
				cout << "Hodnota: ";
				cin >> hodnota;
				if(!s->vloz_za(za, hodnota)) cerr << "CHYBA: Prvek nenalezen." << endl;
			break;
			case 7:
				s->vypsat();
			break;
			case 8:
				s->vymaz();
			break;
			default:
				return 0;
			break;
		}
	}
		
	return 0;
}
