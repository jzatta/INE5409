#ifndef ELEMENT_HPP
#define ELEMENT_HPP

#include <cstdlib>

template<typename T>
class Element {
private:
    Element<T> *_next, *_prev;
    T *_info;
public:
    Element(Element<T> *next, T *info) {
        _next = next;
        _prev = NULL;
        _info = info;
    }
    
    Element(Element<T> *next, Element<T> *prev, T *info) {
        _next = next;
        _prev = prev;
        _info = info;
    }
    
    void setNext(Element<T> *next) {
        _next = next;
    }
    
    void setPrev(Element<T> *prev) {
        _prev = prev;
    }
    
    Element<T> *getNext() {
        return _next;
    }
    
    Element<T> *getPrev() {
        return _prev;
    }
    
    T *getInfo(){
        return _info;
    }
};
#endif
