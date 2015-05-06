
#include "Event.h"

#include "Eventable.h"

#include "debug.h"

Event::Event(Eventable *_evt, void (*_callBack)(Eventable*, int), int _time) {
    evt = _evt;
    callBack = _callBack;
    time = _time;
}

Event::~Event() {}

int Event::getTime() {
    return time;
}

void Event::handleEvent() {
    callBack(evt, time);
    delete this;
}

bool Event::operator>(Event *evt) {
    if (this->time > evt->time)
        return true;
    return false;
}

bool Event::operator<(Event *evt) {
    if (this->time < evt->time)
        return true;
    return false;
}

bool Event::operator==(Event *evt) {
    if (this->time == evt->time)
        return true;
    return false;
}
