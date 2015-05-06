#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include "Eventable.h"

class Track;

template<typename T>
class List;

enum Directions {DIRWE, DIRNS, DIREW, DIRSN};

class Semaphores: public Eventable {
private:
    static List<Track> *tracksToNotify[4];
    int counterTracks[4];
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
