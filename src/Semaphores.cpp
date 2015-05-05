
#include "Semaphore.h"

Semaphores::Semaphores(int time) {
    timeChange = time;
    for (i = 0; i < 4; i++)
        tracksToSem[i] = new List<Track>();
    openedDirection = -1;
    execute(0-time);
}

virtual Semaphores::~Semaphores() {
    for (i = 0; i < 4; i++)
        delete tracksToSem[i];
}

void Semaphores::addTrack(Track *t, int direction) {
    tracksToNotify[direction]->add(t,0);
}

static void Semaphores::execute(Eventable *target, int evtTime) {
    ((Semaphores*)target)->execute(evtTime);
}

void Semaphores::execute(int evtTime) {
    for (int j = 0; !tracksToNotify[openedDirection]->empty(); j++)
        tracksToNotify[openedDirection]->get(j)->semaphoreBlock(evtTime);
    openedDirection = ++openedDirection % 4;
    Event* evt = new Event(this, &execute,  evtTime + timeChange);
    Manager::getEvents()->add(evt);
    for (int j = 0; !tracksToNotify[openedDirection]->empty(); j++)
        tracksToNotify[openedDirection]->get(j)->semaphoreUnblock(evtTime);
}
