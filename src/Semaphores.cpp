
#include "Semaphores.h"

#include "Eventable.h"
#include "Event.h"
#include "List.hpp"
#include "Manager.h"
#include "SortedList.hpp"
#include "Track.h"
#include "SourceTrack.h"
#include "SinkTrack.h"
#include "LinkTrack.h"

List<Track> *Semaphores::tracksToNotify[4];

Semaphores::Semaphores(int time) {
    int i;
    timeChange = time;
    for (i = 0; i < 4; i++) {
        tracksToNotify[i] = new List<Track>();
        counterTracks[i] = 0;
    }
    openedDirection = 3;
    execute(0-time);
}

Semaphores::~Semaphores() {
    int i;
    for (i = 0; i < 4; i++)
        delete tracksToNotify[i];
}

void Semaphores::addTrack(Track *t, int direction) {
    counterTracks[direction]++;
    tracksToNotify[direction]->add(t,0);
}

void Semaphores::execute(Eventable *target, int evtTime) {
    println("Semaphores:s:execute()" << evtTime);
    ((Semaphores*)target)->execute(evtTime);
}

void Semaphores::execute(int evtTime) {
    println("Semaphores::execute()" << evtTime);
    for (int j = 0; j < counterTracks[openedDirection]; j++) {
        tracksToNotify[openedDirection]->get(j)->semaphoreBlock(evtTime);
    }
    openedDirection = ++openedDirection % 4;
    Event* evt = new Event(this, &Semaphores::execute, evtTime + timeChange);
    if (evt == NULL)
        throw "Null Event";
    Manager::getEvents()->add(evt);
    for (int j = 0; j < counterTracks[openedDirection]; j++)
        tracksToNotify[openedDirection]->get(j)->semaphoreUnblock(evtTime);
}
