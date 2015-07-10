#include <iostream>
#include "matice.h"
#include "autopointer.h"

int main()
{
    CAutoPtr ptr(new CMatice(3));
    cout << ptr->stopa() << endl;
    return 0;
}
