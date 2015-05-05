#ifndef SOURCETRACK_H
#define SOURCETRACK_H

#include <cstdlib>
#include "Event.hpp"
#include "Manager.hpp"
#include "Track.hpp"
#include "Vehicle.hpp"

class SourceTrack: public Track {
private:
    int timeGenerate, variation;
    bool semaphoreRed, carWaitingSemaphore;
public:
    SourceTrack(int lenght, int velocity, int time, int var): Track(int lenght, int velocity);
    
    virtual ~SourceTrack();
    
    static void createCar(Eventable *target, int evtTime);
    
    void createCar(int evtTime);
    
    void waitingSemaphore();
    
    void semaphoreUnblock(int evtTime);
    
    void semaphoreBlock(int evtTime);
    
    bool semaphoreBlocked();
};
#endif
