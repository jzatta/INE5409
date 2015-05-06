#ifndef LIST_HPP
#define LIST_HPP

#include "Element.hpp"

#include "debug.h"

template<typename T>
class List {
protected:
    Element<T> *head;
    int size;
    Element<T> *memPos(int pos) {
        int i;
        Element<T> *posPtr = head;
        if (pos < 0)
            throw -1;
        for (i = 0; i < pos; i++) {
            posPtr = posPtr->getNext();
            if (posPtr == NULL)
                throw -1;
        }
        return posPtr;
    }
    
public:
    List() {
        head = NULL;
        size = 0;
    }
    
    virtual ~List() {}
    
    virtual void add(T *data, int pos) {
        Element<T> *prevPosPtr, *tmpPtr;
        if (pos == 0) {
            addBegin(data);
            return;
        }
        prevPosPtr = memPos(pos - 1);
        tmpPtr = new Element<T>(prevPosPtr->getNext(), data);
        if (tmpPtr == NULL)
            throw -1;
        size++;
        prevPosPtr->setNext(tmpPtr);
        return;
    }
    
    virtual void add(T *data) {
        add(data,size);
    }
    
    T *get(int pos) {
        if (empty())
            throw -1;
        if (pos == 0) {
            return head->getInfo();
        }
        return memPos(pos - 1)->getNext()->getInfo();
    }
    
    T *remove(int pos) {
        Element<T> *prevPosPtr, *delPtr;
        if (empty())
            throw -1;
        if (pos == 0) {
            return removeBegin();
        }
        size--;
        prevPosPtr = memPos(pos - 1);
        delPtr = prevPosPtr->getNext();
        T *retData = delPtr->getInfo();
        prevPosPtr->setNext(delPtr->getNext());
        delete delPtr;
        return retData;
    }
    
    void addBegin(T *data) {
        Element<T> *tmpPtr;
        tmpPtr = new Element<T>(head, data);
        if (tmpPtr == NULL) {
            throw -1;
        }
        size++;
        head = tmpPtr;
        return;
    }

    T *removeBegin() {
        Element<T> *tmpPtr = head;
        if (empty())
            throw -1;
        size--;
        T *info = head->getInfo();
        head = head->getNext();
        delete tmpPtr;
        return info;
    }
    
    bool empty() {
        return head == NULL;
    }
};
#endif
