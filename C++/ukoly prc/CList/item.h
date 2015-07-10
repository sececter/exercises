#ifndef ITEM_H_INCLUDED
#define ITEM_H_INCLUDED

template<typename T>
class CItem{
    CItem<T>* prev;
    CItem<T>* next;
    T data;
public:
    CItem() { prev = nullptr; next = nullptr;}
    void setData(T d0) {data = d0;}
    T getData() const {return data;}
    template<typename X> friend class CList;
};

#endif // ITEM_H_INCLUDED
