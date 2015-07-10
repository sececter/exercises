#include <iostream>
#include <string>
#include "bin_strom.cpp"
#include "util.cpp"
#define _DEBUG

using namespace std;

int main(int argc, const char** argv) {
	cout << "Vitejte v implementaci binarniho stromu." << endl;
	bstrom b;
	
	int vyber;
	
	while(true) {
		cout << "*********************" << endl;
		cout << "Menu:" << endl;
		cout << "1. vlozit prvek do stromu" << endl;
		cout << "2. vyjmout prvek ze stromu" << endl;
		cout << "3. najit prvek ve strome" << endl;
		cout << "4. zobrazit strom" << endl;
		cout << "5. vyska stromu" << endl;
		cout << "6. nacist strom ze souboru" << endl;
		cout << "0. konec" << endl;
		cout << "Zadejte vasi volbu: ";
		cin >> vyber;
		switch(vyber) {
			case 1: {
				data_t vkladany = 0;
				cout << "Zadejte hodnotu, kterou si prejete vlozit (cele cislo): ";
				cin >> vkladany;
				if(je_cislo(vkladany)) {
					b.vloz_uzel(vkladany);
				} else {
					cout << "Tato hodnota neni celym cislem." << endl;
				}
			}
			break;
			case 2: {
				if(b.vrat_koren() == NULL) {
					cout << "Neni co mazat, strom je prazdny." << endl;
				} else {
					data_t mazany = 0;
					cout << "Vlozte hodnotu prvku, ktery si prejete smazat: ";
					cin >> mazany;
					if(b.smaz_uzel(mazany)) {
						cout << "Uzel uspesne smazan." << endl;
					} else {
						cout << "Uzel nebyl nalezen." << endl;
					}
				}
			}
			break;
			case 3: {
				data_t hledany = 0;
				uzel* predchudce = 0;
				cout << "Zadejte hodnotu prvku, ktery se chcete pokusit nalezt: ";
				cin >> hledany;
				uzel* nalezeny;
				nalezeny = b.najdi_uzel(hledany, b.vrat_koren(), predchudce);
				if(nalezeny != NULL) cout << "Prvek nalezen." << endl;
				else cout << "Prvek nenalezen." << endl;
			}
			break;
			case 4: {
				cout << "Zatim pouze testovaci verze. Pribude lepsi zpusob vystupu." << endl;
				b.vytiskni_strom();
			}
			break;
			case 0: {
				cout << "Navidenou." << endl;
			}
			break;
			default:
				cout << "Vase volba neni podporovana. Zkuste to znovu." << endl;
		}
	}
	return 0;
}
