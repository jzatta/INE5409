
#include "Track.h"

#include <cstdlib>
#include "Eventable.h"
#include "Event.h"
#include "List.hpp"
#include "Manager.h"
#include "Queue.hpp"
#include "SortedList.hpp"
#include "Vehicle.h"

Track::Track(int lenght, int velocity){
    this->totalLenght = lenght;
    this->velocity = (int)((double)velocity / 3.6);
    this->usedLenght = 0;
    trackBlocked = false;
    trafficJam = 0;
    cars = new Queue<Vehicle>();
    targetTracks = new List<Track>();
    targetProbability = new List<int>();
    waitingTracks = new List<Track>();
    carsIn = carsOut = 0;
}

Track::~Track() {
    while (!cars->empty())
        delete cars->remove();
    while (!targetProbability->empty())
        delete targetProbability->remove(0);
    delete cars;
    delete targetTracks;
    delete targetProbability;
    delete waitingTracks;
}

void Track::addTargetTracks(Track *track, int prob) {
    targetTracks->add(track,0);
    /* Ignorar */
    targetProbability->add(new int(prob),0);
    /* Gambiarra pra nao precisar mudar as listas */
}

bool Track::incoming(Vehicle *car) {
    if ((totalLenght - usedLenght) >= car->getLenght()) {
        carsIn++;
        cars->add(car);
        car->setupDir(-1);
        usedLenght += car->getLenght();
        int timeToGetOut = ( totalLenght - car->getLenght() ) / velocity;
        generateEvent(timeToGetOut);
        return true;
    }
    return false;
}

void Track::outgoing(Eventable *target, int evtTime) {
    println("Track:s:outgoing");
    ((Track*)target)->outgoing(evtTime);
}

void Track::outgoing(int evtTime) {
    println("Track::outgoing");
    if (trackBlocked){
        trafficJam++;
        return;
    }
    // threat semaphore if open continue, else block track and add to semaphore notify
    if (semaphoreBlocked()) {
    println("Track::outgoing::blockedSem");
        waitingSemaphore();
        return;
    }
    //if (cars->empty())
    //    return;
    Vehicle *car = cars->get();
    int destination = car->getDirection();
    if (destination == -1) {
        int totalChances = 0, i;
        for (i = 0; i < targetProbability->sizeOf(); i++) {
            totalChances += *(targetProbability->get(i));
        }
        totalChances = std::rand() % totalChances;
        for (i = 0; totalChances >= 0; i++) {
            totalChances -= *(targetProbability->get(i));
            if (totalChances < 0)
                break;
        }
        destination = i;
        car->setupDir(destination);
        println("Track::outgoing::dirCalculated");
    }
    println("Track::outgoing::dirCalculated" << destination);
    bool test = targetTracks->get(destination)->incoming(car);
    println("Track::outgoing::tryIncoming" << test);
    if (test) {
        carsOut++;
        cars->remove();
        usedLenght -= car->getLenght();
        if (trafficJam) {
            trafficJam--;
            int timeToGetOut = car->getLenght() / velocity;
            generateEvent(evtTime + timeToGetOut);
        }
        while (!waitingTracks->empty())
            waitingTracks->remove(0)->notify(evtTime);
        return;
    }
    trackBlocked = true;
    targetTracks->get(destination)->waitingFor(this);
}

void Track::notify(int evtTime) {
    println("Track::notify");
    trackBlocked = false;
    outgoing(evtTime);
}

void Track::waitingFor(Track *t) {
    waitingTracks->add(t);
}

void *Track::generateEvent(int time) {
    Event* evt = new Event(this, &Track::outgoing,  time);
    Manager::getEvents()->add(evt);
}

int Track::getCarsIn() {
    return carsIn;
}
int Track::getCarsOut(){
    return carsOut;
}
