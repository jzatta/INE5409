#ifndef SEMAPHORE_HPP
#define SEMAPHORE_HPP

#include "Eventable.hpp"
#include "Event.hpp"
#include "List.hpp"
#include "Manager.hpp"
#include "Track.hpp"

enum Directions {DIRWE, DIRNS, DIREW, DIRSN};

class Semaphores: public Eventable {
private:
    List<Track> *tracksToNotify[4];
    int timeChange;
    int openedDirection;
public:
    Semaphores(int time) {
        timeChange = time;
        for (i = 0; i < 4; i++)
            tracksToSem[i] = new List<Track>();
        openedDirection = -1;
        execute(0-time);
    }
    
    ~Semaphores() {
        for (i = 0; i < 4; i++)
            delete tracksToSem[i];
    }
    
    void addTrack(Track *t, int direction) {
        tracksToNotify[direction]->add(t,0);
    }
    
    void execute(int evtTime) {
        for (int j = 0; !tracksToNotify[openedDirection]->empty(); j++)
            tracksToNotify[openedDirection]->get(j)->semaphoreBlock(evtTime);
        openedDirection = ++openedDirection % 4;
        Event* evt = new Event(this, &execute,  evtTime + timeChange);
        Manager::getEvents()->add(evt);
        for (int j = 0; !tracksToNotify[openedDirection]->empty(); j++)
            tracksToNotify[openedDirection]->get(j)->semaphoreUnblock(evtTime);
    }
};
#endif
