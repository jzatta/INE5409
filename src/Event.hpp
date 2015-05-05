
#include "Eventable.hpp"

class Event {
private:
    int time;
    Eventable *evt;
    void (*callBack)(Event*);
public:
    Event(Eventable *_evt, void (*_callBack)(int)  int _time) {
        evt = _evt;
        callBack = _callBack;
        time = _time;
    }
    
    virtual ~Event() {
        
    }
    
    int getTime() {
        return time;
    }
    
    void handleEvent() {
        evt->callBack(time);
        delete this;
    }
    
    bool operator>(Event *evt) {
        if (this->time > evt->time)
            return true;
        return false;
    }
    
    bool operator<(Event *evt) {
        if (this->time < evt->time)
            return true;
        return false;
    }
    
    bool operator==(Event *evt) {
        if (this->time == evt->time)
            return true;
        return false;
    }
};
