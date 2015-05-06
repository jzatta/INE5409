#ifndef TRACK_H
#define TRACK_H

#include "Eventable.h"

class Vehicle;

template<typename T>
class List;
template<typename T>
class Queue;
template<typename T>
class SortedList;

class Track: public Eventable {
protected:
    Queue<Vehicle> *cars;
    List<Track> *targetTracks;
    List<int> *targetProbability;
    List<Track> *waitingTracks;
    bool trackBlocked;
    int trafficJam;
    int totalLenght, usedLenght, velocity; // All saved in SI
    int carsIn, carsOut;
public:
    Track(int lenght, int velocity);
    
    virtual ~Track();
    
    void addTargetTracks(Track *track, int prob);

    bool incoming(Vehicle *car);
    
    static void outgoing(Eventable *target, int evtTime);

    virtual void outgoing(int evtTime);
    
    void notify(int evtTime);
    
    void waitingFor(Track *t);
    
    void *generateEvent(int time);
    
    int getCarsIn();
    int getCarsOut();
    
    virtual void waitingSemaphore() = 0;
    virtual void semaphoreUnblock(int evtTime) = 0;
    virtual void semaphoreBlock(int evtTime) = 0;
    virtual bool semaphoreBlocked() = 0;
};
#endif
