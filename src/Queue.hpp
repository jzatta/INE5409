#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "Element.hpp"

template<typename T>
class Queue {
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
            throw "Queue::add: is full";
        if (empty())
            head = tmpPtr;
        else
            tail->setNext(tmpPtr);
        tail = tmpPtr;
    }
    
    T *get() {
        if (empty())
            throw "Queue::get: is empty";
        return head->getInfo();
    }
    
    T *remove() {
        Element<T> *delPtr;
        T *data = get();
        if (empty())
            throw "Queue::remove: is empty";
        delPtr = head;
        head = head->getNext();
        delete delPtr;
        return data;
    }
    
    bool empty() {
        return head == NULL;
    }
};
#endif
