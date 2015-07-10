#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include <iostream>
#include "item.h"

template<typename T>
class CList{
    CItem<T> *first;
    CItem<T> *last;
public:
    CList();
    ~CList(){
        clean();
        delete first;
        delete last;
    }
    void clean(){
        while(!empty())
            pop_front();
    }
    bool empty(){
        return (first->next == last);
    }
    void print();
    T pop_front();
    T pop_back();
    CItem<T>* find(T d);
    void push_back(T d);
    void push_front(T d);
    CItem<T>* findMinimum(CItem<T> *i);
    void swap(CItem<T> *a, CItem<T> *b);
    void sort();
};

template<typename T>
CItem<T>* CList<T>::find(T d){
    last->setData(d);
    CItem<T> *iter = first->next;
    while(iter->getData()!=d)
        iter = iter->next;
    if(iter == last)
        return nullptr;
    else
        return iter;
}


template<typename T>
CList<T>::CList()
: first(new CItem<T>), last(new CItem<T>)
{
    first->next = last;
    last->prev = first;
}

template<typename T>
void CList<T>::print(){
    CItem<T> *iter = first->next;
    while(iter!=last){
        std::cout << iter->getData() << std::endl;
        iter = iter->next;
    }
}

template<typename T>
T CList<T>::pop_front(){
    first = first->next;
    delete first->prev;
    first->prev = nullptr;
    return first->getData();
}


template<typename T>
T CList<T>::pop_back(){
    last = last->prev;
    delete last->next;
    last->next = nullptr;
    return last->getData();
}

template<typename T>
void CList<T>::push_back(T d){
    CItem<T> *tmp = new CItem<T>;
    last->setData(d);
    last->next = tmp;
    tmp->prev = last;
    last = tmp;
}

template<typename T>
void CList<T>::push_front(T d){
    CItem<T> *tmp = new CItem<T>;
    first->setData(d);
    first->prev = tmp;
    tmp->next = first;
    first = tmp;
}

template<typename T>
CItem<T>* CList<T>::findMinimum(CItem<T> *i){
	CItem<T> *min = i;
	CItem<T> *iter = i->next;
	while(iter != last){
		if(iter->getData() < min->getData())
			min = iter;
		iter = iter->next;
	}
	return min;
}

template<typename T>
void CList<T>::swap(CItem<T> *a, CItem<T> *b){
	T tmp = a->getData();
	a->setData(b->getData());
	b->setData(tmp);
}

template<typename T>
void CList<T>::sort(){
	CItem<T> *iter = first->next;
	CItem<T> *min;
	while(iter != last) {
		min = findMinimum(iter);
		swap(min, iter);
		iter = iter->next;
	}	
}

#endif // LIST_H_INCLUDED
