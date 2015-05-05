
#include "SinkTrack.h"

SinkTrack::SinkTrack(int lenght, int velocity): Track(int lenght, int velocity) {}

virtual SinkTrack::~SinkTrack() {}

void SinkTrack::waitingSemaphore() {}

void SinkTrack::semaphoreUnblock(int evtTime) {}

void SinkTrack::semaphoreBlock(int evtTime) {}

bool SinkTrack::semaphoreBlocked() {
    return false;
}

virtual void SinkTrack::outgoing(int evtTime) {
    Vehicle *car = cars->get();
    usedLenght -= car->getLenght();
    while (!waitingTracks->empty())
        waitingTracks->remove()->notify(evtTime);
    delete cars->remove();
    return;
}
