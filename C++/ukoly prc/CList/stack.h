#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include "list.h"

template<typename T>
class CStack{
    CList<T> l;
public:
    bool empty(){return l.empty();}
    void push(T d){l.push_back(d);}
    T pop(){return l.pop_back();}
};


#endif // STACK_H_INCLUDED
