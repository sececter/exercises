#include <iostream>
#include "matice.h"

using namespace std;

CMatice::CMatice(float diag)
{
    d = new float* [dim];
    for(int i = 0; i < dim; i++)
        d[i] = new float[dim];
    for(int i = 0; i < dim; i++)
        for(int j = 0; j < dim; j++) {
            if(i == j) d[i][i] = diag;
            else d[i][j] = 0;
        }
}

CMatice::CMatice(const CMatice &other)
{
    d = new float* [dim];
    for(int i = 0; i < dim; i++)
        d[i] = new float[dim];
    for(int i = 0; i < dim; i++)
        for(int j = 0; j < dim; j++) {
            d[i][j] = other.d[i][j];
        }
}

CMatice::~CMatice()
{
    for(int i = 0; i < dim; i++)
        delete[] d[i];
    delete[] d;
}

float CMatice::stopa() {
    float s = 0;
    for(int i = 0; i < dim; i++)
        s = s + d[i][i];
    return s;
}

float& CMatice::operator ()(int i, int j)
{
   if(i >= 0 && i < dim && j >= 0 && j < dim)
        return d[i][j];
   else
       cerr << "Index mimo meze" << endl;
}

float* CMatice::operator [](int i)
{
    return d[i];
}

CMatice CMatice::operator=(const CMatice rhs)
{
    if(this == &rhs)
        return *this;
    for(int i = 0; i < dim; i++)
        for(int j = 0; j < dim; j++)
            this->d[i][j] = rhs.d[i][j];
    return *this;
}

CMatice operator+(const CMatice &a, const CMatice &b)
{
    CMatice c;
    for(int i = 0; i < CMatice::dim; i++)
        c.d[i] = new float[CMatice::dim];
    for(int i = 0; i < CMatice::dim; i++)
        for(int j = 0; j < CMatice::dim; j++) {
            c.d[i][j] = a.d[i][j] + b.d[i][j];
        }
    return c;
}

CMatice operator-(const CMatice &a, const CMatice &b)
{
    CMatice c;
    for(int i = 0; i < CMatice::dim; i++)
        c.d[i] = new float[CMatice::dim];
    for(int i = 0; i < CMatice::dim; i++)
        for(int j = 0; j < CMatice::dim; j++) {
            c.d[i][j] = a.d[i][j] - b.d[i][j];
        }
    return c;
}

CMatice operator*(const CMatice &a, const CMatice &b)
{
    CMatice c;
    for(int i = 0; i < CMatice::dim; i++)
        c.d[i] = new float[CMatice::dim];
    for(int i = 0; i < CMatice::dim; i++)
        for(int j = 0; j < CMatice::dim; j++) {
            c.d[i][j] = 0;
            for(int k = 0; k < CMatice::dim; k++)
                c.d[i][j] += a.d[i][k] * b.d[k][j];
        }
    return c;
}

CMatice operator-(const CMatice &a)
{
    CMatice c;
    for(int i = 0; i < CMatice::dim; i++)
        c.d[i] = new float[CMatice::dim];
    for(int i = 0; i < CMatice::dim; i++)
        for(int j = 0; j < CMatice::dim; j++) {
            c.d[i][j] = -a.d[i][j];
        }
    return c;
}

CMatice transpose(const CMatice &a)
{
    CMatice c;
    for(int i = 0; i < CMatice::dim; i++)
        c.d[i] = new float[CMatice::dim];
    for(int i = 0; i < CMatice::dim; i++)
        for(int j = 0; j < CMatice::dim; j++)
            c.d[i][j] = a.d[j][i];
    return c;
}

ostream& operator<<(ostream &ost, const CMatice &c)
{
    for(int i = 0; i < c.dim; i++){
        for(int j = 0; j < c.dim; j++) {
            ost << " " << c.d[i][j] << "\t";
        }
        ost << endl;
    }
    return ost;
}
