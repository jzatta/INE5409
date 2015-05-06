#ifndef SORTEDLIST_HPP
#define SORTEDLIST_HPP

#include "Element.hpp"
#include "List.hpp"

template<typename T>
class SortedList: public List<T> {
private:
    
public:
    SortedList(): List<T>() {}
    
    virtual ~SortedList() {}
    
    void add(T *data) {
        Element<T> *tmpPtr, *posPtr;
        if ( this->head == NULL || data->operator<(this->head->getInfo()) ) {
            this->addBegin(data);
            return;
        }
        posPtr = this->head;
        while ( (tmpPtr = posPtr->getNext()) != NULL ) {
            if ( data->operator<(tmpPtr->getInfo()) )
                break;
            posPtr = tmpPtr;
        }
        tmpPtr = new Element<T>(tmpPtr, data);
        if (tmpPtr == NULL)
            throw "SortedList::add: is full";
        posPtr->setNext(tmpPtr);
    }
};
#endif
