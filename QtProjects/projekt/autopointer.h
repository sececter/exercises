#ifndef AUTOPOINTER_H
#define AUTOPOINTER_H

class CMatice;

class CAutoPtr
{
    bool vlastnik;
    CMatice *pm;
public:
    CAutoPtr(CMatice *pmat);
    CAutoPtr(CAutoPtr &other);
    ~CAutoPtr();
    CAutoPtr& operator=(CAutoPtr &rhs);
    CMatice* operator->();
};

#endif // AUTOPOINTER_H
