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
        if ( this->head == NULL || (*data < *(this->head->getInfo())) ) {
            addBegin(data);
            return;
        }
        posPtr = this->head;
        while ( (tmpPtr = posPtr->getNext()) != NULL ) {
            if ( *data < *(this->head->getInfo()) )
                break;
        }
        tmpPtr = new Element<T>(tmpPtr, data);
        if (tmpPtr == NULL)
            throw -1;
        posPtr->setNext(tmpPtr);
    }
};
#endif
