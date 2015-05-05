
#include "LinkTrack.h"

LinkTrack::LinkTrack(int lenght, int velocity): Track(int lenght, int velocity) {
    semaphoreRed = true;
    carWaitingSemaphore = false;
}

virtual LinkTrack::~LinkTrack() {}

void LinkTrack::waitingSemaphore() {
    carWaitingSemaphore = true;
}

void LinkTrack::semaphoreUnblock(int evtTime) {
    semaphoreRed = false;
    if (carWaitingSemaphore){
        carWaitingSemaphore = false;
        outgoing(evtTime);
    }
}

void LinkTrack::semaphoreBlock(int evtTime) {
    semaphoreRed = true;
}

bool LinkTrack::semaphoreBlocked() {
    return semaphoreRed;
}
