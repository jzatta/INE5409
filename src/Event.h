#ifndef EVENT_H
#define EVENT_H

#include "Eventable.hpp"

class Event {
private:
    int time;
    Eventable *evt;
    void (*callBack)(Eventable*, int);
public:
    Event(Eventable *_evt, void (*_callBack)(Eventable*, int), int _time);
    
    virtual ~Event();
    
    int getTime();
    
    void handleEvent();
    
    bool operator>(Event *evt);
    
    bool operator<(Event *evt);
    
    bool operator==(Event *evt);
};
#endif
