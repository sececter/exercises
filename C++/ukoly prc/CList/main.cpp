#include <iostream>
#include "stack.h"

using namespace std;

int main()
{
    CList<int> s;
    s.push_back(5);
    s.push_back(8);
    s.push_back(2);
    s.push_back(3);
    s.push_back(9);
    s.push_back(1);
    s.push_back(4);
    s.push_back(6);
    s.push_back(7);
    cout << "Pred serazenim: " << endl;
    s.print();
    cout << endl;
    cout << "Po serazeni: " << endl;
    s.sort();
    s.print();
    return 0;
}
