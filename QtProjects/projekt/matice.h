#ifndef MATICE_H
#define MATICE_H

/* Pretizit operatory pro nasobeni, rozdil, transpozice
 * Tyto lze pretizit obema zpusoby
 *
*/

#include <iostream>

using namespace std;

class CMatice
{
    enum{dim = 3};
    float **d;
public:
    CMatice(float diag = 0);
    CMatice(const CMatice &other);
    ~CMatice();
    float stopa();
    CMatice operator=(CMatice rhs);
    float& operator()(int i, int j);
    float* operator[](int i );
    friend CMatice operator+(const CMatice &a, const CMatice &b);
    friend CMatice operator-(const CMatice &a, const CMatice &b);
    friend CMatice operator-(const CMatice &a);
    friend CMatice operator*(const CMatice &a, const CMatice &b);
    friend CMatice transpose(const CMatice &a);
    friend ostream& operator<<(ostream &ost, const CMatice &c);
};

#endif // MATICE_H
