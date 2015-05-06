
#include "SourceTrack.h"

#include <cstdlib>
#include "Event.h"
#include "Manager.h"
#include "SortedList.hpp"
#include "Track.h"
#include "Vehicle.h"

#include "debug.h"

SourceTrack::SourceTrack(int lenght, int velocity, int time, int var): Track(lenght, velocity) {
    timeGenerate = time;
    variation = var;
    semaphoreRed = true;
    carWaitingSemaphore = false;
    createCar(0);
}

SourceTrack::~SourceTrack() {}

void SourceTrack::createCar(Eventable *target, int evtTime) {
    ((SourceTrack*)target)->createCar(evtTime);
}

void SourceTrack::createCar(int evtTime) {
    println("SourceTrack::createCar()" << evtTime);
    Vehicle *car;
    int timeToAdd = (std::rand() % (variation * 2)) + timeGenerate - variation;
    Event* newEvt = new Event(this, &SourceTrack::createCar, evtTime + timeToAdd);
    Manager::getEvents()->add(newEvt);
    if (evtTime == 0)
        return; // Start of clock;
    car = new Vehicle(Vehicle::ramdomSize());
    if (this->incoming(car))
        return;
    delete car;
}

void SourceTrack::waitingSemaphore() {
    if (carWaitingSemaphore)
        this->trafficJam++;
    carWaitingSemaphore = true;
}
void SourceTrack::semaphoreUnblock(int evtTime) {
    semaphoreRed = false;
    if (carWaitingSemaphore){
        carWaitingSemaphore = false;
        println("LinkTrack::semaphoreUnblock");
        this->outgoing(evtTime);
    }
}
void SourceTrack::semaphoreBlock(int evtTime) {
    semaphoreRed = true;
}

bool SourceTrack::semaphoreBlocked() {
    return semaphoreRed;
}
