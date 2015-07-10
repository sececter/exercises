#include "hra.h"
#include <new>
#include <string>

/* Trida predstavujici danou hru. Vytvorenim instance se
 * vyresi hra se tremi vezemi pro pocet disku predanych
 * v argumentu konstruktoru. Postup se prubezne uklada do
 * pole stavu.
 */

using namespace std;

//Vytvori instance vezi, inicializuje parametry a pole stavu hry.
Hra::Hra(int disku) {
    l = new(nothrow) Vez(disku);
    s = new(nothrow) Vez(disku);
    p = new(nothrow) Vez(disku);
    if(!l || !s || !p) throw chyba_hra("Chyba pri inicializaci vezi!");
    this->disku = disku;
    kroku = (1<<disku) - 1;
    stavy = new stav_hry[kroku+1];
    for(int i = 0; i <= kroku+1; i++) {
        stavy[i].l.vyska = 0;
        stavy[i].s.vyska = 0;
        stavy[i].p.vyska = 0;
        stavy[i].l.disky = new(nothrow) int[disku];
        stavy[i].s.disky = new(nothrow) int[disku];
        stavy[i].p.disky = new(nothrow) int[disku];
        if(!stavy[i].l.disky || !stavy[i].s.disky || !stavy[i].p.disky) throw chyba_hra("Chyba pri inicializaci stavu " + i);
    }
    vyres();
}

//Destruktor.
Hra::~Hra() {
    delete l;
    delete s;
    delete p;
    delete[] stavy;
}

//Vrati stav_hry v i-tem kroku.
stav_hry Hra::stav_v_kroku(int i) {
    if(i > kroku+1) throw chyba_hra("Index mimo meze - pole: stavy, index: " + i);
    return stavy[i];
}

//Provede legalni presun mezi dvema vezema.
void Hra::presun(Vez *z, Vez *na, int krok) {
    int diskz = z->sejmi_disk();
    int diskna = na->sejmi_disk();

    //Jedna z vezi byla prazdna - nevymeni, pouze nasadi.
    if(diskz == -1) {
        z->nasad_disk(diskna);
    }
    else if(diskna == -1) {
        na->nasad_disk(diskz);
    }
    //vymeni
    else if(diskz > diskna) {
        z->nasad_disk(diskz);
        z->nasad_disk(diskna);
    }
    else if(diskz < diskna) {
        na->nasad_disk(diskna);
        na->nasad_disk(diskz);
    }
    uloz_stav(krok);
}

//Ulozi vysku a zkopiruje pole disku do zaznamu o stavu.
void Hra::uloz_stav(int krok) {
    stavy[krok].l.vyska = l->vyska();
    stavy[krok].s.vyska = s->vyska();
    stavy[krok].p.vyska = p->vyska();
    for(int i = 0; i < l->vyska(); i++) {
        stavy[krok].l.disky[i] = (*l)[i];
    }
    for(int i = 0; i < s->vyska(); i++) {
        stavy[krok].s.disky[i] = (*s)[i];
    }
    for(int i = 0; i < p->vyska(); i++) {
        stavy[krok].p.disky[i] = (*p)[i];
    }
}

void Hra::vyres() {
    //Naplni prvni vez.
    for(int i = disku; i >= 1; i--)
        l->nasad_disk(i);
    uloz_stav(0);
    for(int i = 1; i <= kroku; i++) {
        if(i%3 == 1) presun(l, p, i);
        else if(i%3 == 2) presun(l, s, i);
        else if(i%3 == 0) presun(s, p, i);
    }
}
