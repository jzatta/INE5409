
#include "SinkTrack.h"

#include "List.hpp"
#include "Queue.hpp"
#include "Track.h"
#include "Vehicle.h"

SinkTrack::SinkTrack(int lenght, int velocity): Track(lenght, velocity) {}

SinkTrack::~SinkTrack() {}

void SinkTrack::waitingSemaphore() {}

void SinkTrack::semaphoreUnblock(int evtTime) {}

void SinkTrack::semaphoreBlock(int evtTime) {}

bool SinkTrack::semaphoreBlocked() {
    return false;
}

void SinkTrack::outgoing(int evtTime) {
    println("SinkTrack::outgoing");
    Vehicle *car = cars->get();
    usedLenght -= car->getLenght();
    while (!waitingTracks->empty())
        waitingTracks->remove(0)->notify(evtTime);
    carsOut++;
    delete cars->remove();
    return;
}
