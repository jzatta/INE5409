#ifndef TRACK_H
#define TRACK_H

#include <cstdlib>
#include "Eventable.hpp"
#include "Event.hpp"
#include "List.hpp"
#include "Manager.hpp"
#include "Queue.hpp"
#include "Vehicle.hpp"

class Track: public Eventable {
protected:
    Queue<Vehicle> *cars;
    List<Track> *targetTracks;
    List<int> *targetProbability;
    bool trackBlocked;
    int trafficJam;
    int totalLenght, usedLenght, velocity; // All saved in SI
    List<Track> *waitingTracks;
public:
    Track(int lenght, int velocity);
    
    virtual ~Track();
    
    void addTargetTracks(Track *track, int prob);

    bool Event *incoming(Vehicle *car);
    
    static void outgoing(Eventable *target, int evtTime);

    virtual void outgoing(int evtTime);
    
    void notify(int evtTime);
    
    void waitingFor(Track *t);
    
    void *generateEvent(int time);
    
    void waitingSemaphore();
    void semaphoreUnblock();
    void semaphoreBlock();
    bool semaphoreBlocked();
};
#endif
