
#include "LinkTrack.h"

#include "Track.h"

#include "debug.h"

LinkTrack::LinkTrack(int lenght, int velocity): Track(lenght, velocity) {
    semaphoreRed = true;
    carWaitingSemaphore = false;
}

LinkTrack::~LinkTrack() {}

void LinkTrack::waitingSemaphore() {
    if (carWaitingSemaphore)
        this->trafficJam++;
    carWaitingSemaphore = true;
}

void LinkTrack::semaphoreUnblock(int evtTime) {
    semaphoreRed = false;
    if (carWaitingSemaphore){
        carWaitingSemaphore = false;
        println("LinkTrack::semaphoreUnblock");
        this->outgoing(evtTime);
    }
}

void LinkTrack::semaphoreBlock(int evtTime) {
    semaphoreRed = true;
}

bool LinkTrack::semaphoreBlocked() {
    return semaphoreRed;
}
