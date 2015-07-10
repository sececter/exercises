#include "autopointer.h"
#include "matice.h"

CAutoPtr::CAutoPtr(CMatice *pmat)
    : pm(pmat), vlastnik(true)
{
}

CAutoPtr::CAutoPtr(CAutoPtr &other)
{
    this->pm = other.pm;
    vlastnik = other.vlastnik;
    other.vlastnik = false;
}

CAutoPtr::~CAutoPtr()
{
    if(vlastnik)
        delete pm;
}

CMatice* CAutoPtr::operator ->()
{
    return this->pm;
}

CAutoPtr& CAutoPtr::operator =(CAutoPtr &rhs)
{
    if(vlastnik)
        delete pm;
    this->pm = rhs.pm;
    this->vlastnik = rhs.vlastnik;
    rhs.vlastnik = false;

    return *this;
}
