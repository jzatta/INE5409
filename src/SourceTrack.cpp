
#include "SourceTrack.h"

SourceTrack::SourceTrack(int lenght, int velocity, int time, int var): Track(int lenght, int velocity) {
    timeGenerate = time;
    variation = var;
    semaphoreRed = true;
    carWaitingSemaphore = false;
    createCar(0);
}

virtual SourceTrack::~SourceTrack() {}

static void SourceTrack::createCar(Eventable *target, int evtTime) {
    ((SourceTrack*)target)->createCar(evtTime);
}

void SourceTrack::createCar(int evtTime) {
    Vehicle *car;
    int timeToAdd = (std::rand() % (var * 2)) + timeGenerate - var;
    Event* newEvt = new Event(this, &SourceTrack::createCar, evtTime + timeToAdd);
    Manager::getEvents()->add(newEvt);
    car = new Vehicle(Vehicle::randomSize());
    if (Track::incoming(car))
        return;
    delete car;
}

void SourceTrack::waitingSemaphore() {
    if (carWaitingSemaphore)
        trafficJam++;
    carWaitingSemaphore = true;
}
void SourceTrack::semaphoreUnblock(int evtTime) {
    semaphoreRed = false;
    if (carWaitingSemaphore){
        carWaitingSemaphore = false;
        outgoing(evtTime);
    }
}
void SourceTrack::semaphoreBlock(int evtTime) {
    semaphoreRed = true;
}

bool SourceTrack::semaphoreBlocked() {
    return semaphoreRed;
}
