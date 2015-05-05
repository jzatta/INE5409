#ifndef SOURCETRACK_HPP
#define SOURCETRACK_HPP

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
    SourceTrack(int lenght, int velocity, int time, int var): Track(int lenght, int velocity) {
        timeGenerate = time;
        variation = var;
        semaphoreRed = true;
        carWaitingSemaphore = false;
        createCar(0);
    }
    
    virtual ~SourceTrack() {}
    
    void createCar(int evtTime) {
        Vehicle *car;
        int timeToAdd = (std::rand() % (var * 2)) + timeGenerate - var;
        Event* newEvt = new Event(this, &createCar, evtTime + timeToAdd);
        Manager::getEvents()->add(newEvt);
        car = new Vehicle(Vehicle::randomSize());
        if (Track::incoming(car))
            return;
        delete car;
    }
    
    void waitingSemaphore() {
        if (carWaitingSemaphore)
            trafficJam++;
        carWaitingSemaphore = true;
    }
    void semaphoreUnblock(int evtTime) {
        semaphoreRed = false;
        if (carWaitingSemaphore){
            carWaitingSemaphore = false;
            outgoing(evtTime);
        }
    }
    void semaphoreBlock(int evtTime) {
        semaphoreRed = true;
    }
    
    bool semaphoreBlocked() {
        return semaphoreRed;
    }
};
#endif
