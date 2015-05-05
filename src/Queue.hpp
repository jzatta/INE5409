#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "Element.hpp"

template<typename T>
class Queue<T> {
private:
    Element<T> *head, *tail;
public:
    Queue() {
        head = NULL;
        tail = NULL;
    }
    
    virtual ~Queue() {}
    
    void add(T *data) {
        Element<T> *tmpPtr;
        tmpPtr = new Element<T>(NULL, data);
        if (tmpPtr == NULL)
            throw -1;
        if (empty())
            head = tmpPtr;
        else
            tail->setnext(tmpPtr);
        tail = tmpPtr;
    }
    
    T *get() {
        if (empty())
            throw -1;
        return head->getInfo();
    }
    
    T *remove() {
        Element<T> *delPtr;
        T *data = get();
        if (empty())
            throw -1;
        delPtr = head;
        head = head->getnext();
        delete delPtr;
        return data;
    }
    
    bool empty() {
        return head == NULL;
    }
};
#endif
