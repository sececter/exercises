#include "vez.h"
#include <new>
#include <string>

/* Trida predstavujici jednu z vezi v urcitem
 * kroku, obsahuje metody pro manipulaci s disky,
 * zapouzdrzuje informace o discich na
 * vezi (pole cisel disku) a vysce veze pomoci
 * pretizeneho operatoru [] a pristupovych metod.
 */

using namespace std;

//Argumentem konstruktoru je pocet disku
Vez::Vez(int N) {
    disky = new(nothrow) int[N];
    if(!disky) throw chyba_vez("Chyba pri inicializaci pole disku.");
    kapacita = N;
    vrchol = -1;
    for(int i = 0; i < N; i++)
        disky[i] = 0;
}

//Destruktor.
Vez::~Vez() {
    delete[] disky;
}

//Je vez prazdna?
bool Vez::prazdna() {
    return (vrchol == -1);
}

//Je vez plna?
bool Vez::plna() {
    return (vrchol == kapacita-1);
}

//Sejme nejsvrchnejsi disk a vrati jeho cislo.
int Vez::sejmi_disk() {
    if(prazdna()) return -1;
    int ret = disky[vrchol];
    disky[vrchol--] = 0;
    return ret;
}

//Nasadi disk v argumentu na vrchol veze.
void Vez::nasad_disk(int disk) {
    if(plna()) return;
    disky[++vrchol] = disk;
}

//Vrati vysku veze.
int Vez::vyska() {
    return vrchol+1;
}

//Vrati i-ty disk v poradi od nejvetsiho.
int Vez::operator[](int i) {
    if(i > kapacita) throw chyba_vez("Index disku mimo meze! i = " + i);
    return disky[i];
}
