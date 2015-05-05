
#include "List.hpp"

template<typename T>
class SortedList<T>: public List<T> {
private:
    
public:
    
    virtual ~SortedList() {}
    
    void add(T *data) {
        Element<T> *tmpPtr, *posPtr;
        if ( head == NULL || (*data < *(head->getInfo())) ) {
            addBegin(data);
            return;
        }
        posPtr = head;
        while ( (tmpPtr = posPtr->getNext()) != NULL ) {
            if ( *data < *(head->getInfo()) )
                break;
        }
        tmpPtr = new Element<T>(tmpPtr, data);
        if (tmpPtr == NULL)
            throw -1;
        posPtr->setNext(tmpPtr);
    }
};