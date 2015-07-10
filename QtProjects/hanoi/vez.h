#ifndef VEZ_H
#define VEZ_H
#include <exception>
#include <string>

const int MAX_DISKU = 10;
const int MAX_KROKU = (1<<MAX_DISKU)-1;

struct stav_veze { int vyska; int* disky; };

class Vez {
public:
    Vez(int N);
    ~Vez();
    int sejmi_disk();
    void nasad_disk(int disk);
    int vyska();
    int operator[](int i);
private:
    int vrchol;
    int* disky;
    int kapacita;
    bool prazdna();
    bool plna();
};

class chyba_vez: public std::exception {
public:
    chyba_vez(std::string s): msg(s){}
    ~chyba_vez() throw() {}
    const char * what() const throw() { return ("Vyjimka v tride vez: " + msg).c_str(); }
private:
    std::string msg;
};

#endif // VEZ_H
