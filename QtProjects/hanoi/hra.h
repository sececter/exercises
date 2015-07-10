#ifndef HRA_H
#define HRA_H
#include "vez.h"
#include <exception>
#include <string>

struct stav_hry { stav_veze l, s, p; };

class Hra {
public:
    Hra(int disku);
    ~Hra();
    stav_hry stav_v_kroku(int i);
private:
    int disku;
    int kroku;
    Vez *l, *s, *p;
    stav_hry* stavy;
    void presun(Vez *z, Vez *na, int krok);
    void uloz_stav(int krok);
    void vyres();
};

class chyba_hra: public std::exception {
public:
    chyba_hra(std::string s): msg(s){}
    ~chyba_hra() throw() {}
    const char * what() const throw() { return ("Vyjimka v tride hra: " + msg).c_str(); }
private:
    std::string msg;
};

#endif // HRA_H
