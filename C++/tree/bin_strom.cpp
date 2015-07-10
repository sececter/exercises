#include <iostream>
#include "bin_strom.h"
#include "util.cpp"

using namespace std;

uzel::uzel(data_t hodnota) {
	this->hodnota = hodnota;
	this->levy = NULL;
	this->pravy = NULL;
}

uzel::~uzel() {
}

bstrom::bstrom() {
	koren = NULL;
}

bstrom::~bstrom() {
	znic_podstrom(koren);
}

void bstrom::vloz_uzel(data_t hodnota) {
	if(je_cislo(hodnota)) {
		vloz_uzel_r(koren, hodnota);
	} else {
	}
}

bool bstrom::smaz_uzel(data_t hodnota) {
	uzel* predchudce = NULL;
	uzel* mazany = najdi_uzel(hodnota, koren, predchudce);
	if(mazany == NULL) {
		return false;
	}
	if(je_list(mazany)) {
		smaz_list(mazany, predchudce);
	}
	else {
		if(je_ve_vetvi(mazany)) smaz_ve_vetvi(mazany, predchudce);
		else {
			uzel* nejvetsi_mensi = mazany->levy;
			predchudce = mazany;
			while(nejvetsi_mensi->pravy) {
				predchudce = nejvetsi_mensi;
				nejvetsi_mensi = nejvetsi_mensi->pravy;
			}
			mazany->hodnota = nejvetsi_mensi->hodnota;
			if(je_ve_vetvi(mazany)) smaz_ve_vetvi(nejvetsi_mensi, predchudce);
			else smaz_list(nejvetsi_mensi, predchudce);
		}
	}
	return true;
}

void bstrom::vloz_uzel_r(uzel* u, data_t &hodnota) {
	if(!u) u = new uzel(hodnota);
	else {
		if(hodnota == u->hodnota) return;
		if(hodnota < u->hodnota) vloz_uzel_r(u->levy, hodnota);
		else vloz_uzel_r(u->pravy, hodnota);
	}
}	

void bstrom::smaz_list(uzel* u, uzel* predchudce) {
	if(predchudce != NULL) {
		if(predchudce->levy == u) predchudce->levy = NULL;
		else predchudce->pravy = NULL;
	} else {
		koren = NULL;
	}
	delete u;
}

void bstrom::smaz_ve_vetvi(uzel* u, uzel* predchudce) {
	uzel* naslednik;
	u->levy != NULL ? naslednik = u->levy : naslednik = u->pravy;
	if(predchudce != NULL) {
		je_levym_naslednikem(u, predchudce) ? predchudce->levy = naslednik : predchudce->pravy = naslednik;
	} else {
		koren = naslednik;
	}
	delete u;
}

uzel* bstrom::najdi_uzel(data_t hodnota, uzel* tento_uzel, uzel* uzel_predchudce) {
	if(tento_uzel == NULL) return NULL;
	if(tento_uzel->hodnota == hodnota) return tento_uzel;
	uzel_predchudce = tento_uzel;
	if(tento_uzel->hodnota < hodnota) najdi_uzel(hodnota, tento_uzel->pravy, uzel_predchudce);
	else najdi_uzel(hodnota, tento_uzel->levy, uzel_predchudce);
	return NULL;
}

void bstrom::vytiskni_strom() {
	zpracuj_postorder(koren, [](uzel* u) {cout << " " << u->hodnota << " ";});
}

void bstrom::znic_podstrom(uzel* u) {
	zpracuj_postorder(koren, [](uzel* u) {delete u; u = NULL;});
}

void bstrom::zpracuj_inorder(uzel* u, void (*F)(uzel*)) {
	if(u != NULL) {
		zpracuj_inorder(u->levy, F);
		F(u);
		zpracuj_inorder(u->pravy, F);
	}
}

void bstrom::zpracuj_preorder(uzel* u, void (*F)(uzel*)) {
	if(u != NULL) {
		F(u);
		zpracuj_inorder(u->levy, F);
		zpracuj_inorder(u->pravy, F);
	}
}

void bstrom::zpracuj_postorder(uzel* u, void (*F)(uzel*)) {
	if(u != NULL) {
		zpracuj_inorder(u->levy, F);
		zpracuj_inorder(u->pravy, F);
		F(u);
	}
}

uzel* bstrom::vrat_koren() {
	return koren;
}
