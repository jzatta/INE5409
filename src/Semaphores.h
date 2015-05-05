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
    Semaphores(int time);
    
    ~Semaphores();
    
    void addTrack(Track *t, int direction);
    
    static void execute(Eventable *target, int evtTime);
    
    void execute(int evtTime);
};
#endif
